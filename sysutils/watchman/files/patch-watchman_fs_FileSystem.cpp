--- watchman/fs/FileSystem.cpp.orig
+++ watchman/fs/FileSystem.cpp
@@ -14,6 +14,11 @@
 #include "watchman/watchman_stream.h"
 #include "watchman/watchman_string.h"
 
+#ifndef _WIN32
+#include <climits>
+#include <cstdlib>
+#endif
+
 #ifdef __APPLE__
 #include <sys/attr.h> // @manual
 #include <sys/utsname.h> // @manual
@@ -233,7 +238,25 @@ FileDescriptor openFileHandle(
     return file;
   }
 
+  if (opts.create) {
+    // There's nothing useful to canonicalize here: we just created this
+    // file at `path`, so there is no pre-existing canonical name it could
+    // have diverged from.
+    return file;
+  }
+
+#ifdef _WIN32
   auto opened = file.getOpenedPath();
+#else
+  // Resolving the path via the already-open fd (eg: F_GETPATH, F_KINFO)
+  // buys nothing here: it can fail outright or return a different but
+  // equally valid hardlink path, and either way the file could be
+  // renamed the instant after open() returns, so there is no race-free
+  // way to confirm the opened file's identity regardless of mechanism.
+  // Canonicalizing the path string we were asked to open is just as
+  // correct and avoids those extra failure modes.
+  auto opened = realPath(path);
+#endif
   if (w_string_piece(opened).pathIsEqual(path)) {
 #if !CAN_OPEN_SYMLINKS
     CaseSensitivity caseSensitive = opts.caseSensitive;
@@ -318,11 +341,6 @@ w_string getCurrentDirectory() {
 #endif
 
 w_string realPath(const char* path) {
-  auto options = OpenFileHandleOptions::queryFileInfo();
-  // Follow symlinks, because that's really the point of this function
-  options.followSymlinks = 1;
-  options.strictNameChecks = 0;
-
 #ifdef _WIN32
   // Special cases for cwd.
   // On Windows, "" is used to refer to the CWD.
@@ -332,10 +350,24 @@ w_string realPath(const char* path) {
   if (path[0] == 0 || (path[0] == '.' && path[1] == 0)) {
     return getCurrentDirectory();
   }
-#endif
 
+  auto options = OpenFileHandleOptions::queryFileInfo();
+  // Follow symlinks, because that's really the point of this function
+  options.followSymlinks = 1;
+  options.strictNameChecks = 0;
   auto handle = openFileHandle(path, options);
   return handle.getOpenedPath();
+#else
+  // Avoid the overhead of opening a handle purely to query it via
+  // FileDescriptor::getOpenedPath() and closing it again; realpath(3)
+  // resolves the canonical path directly.
+  char resolved[PATH_MAX];
+  if (realpath(path, resolved) == nullptr) {
+    throw std::system_error(
+        errno, std::generic_category(), fmt::format("realpath({})", path));
+  }
+  return w_string(resolved);
+#endif
 }
 
 w_string readSymbolicLink(const char* path) {
