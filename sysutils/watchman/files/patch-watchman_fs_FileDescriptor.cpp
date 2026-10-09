--- watchman/fs/FileDescriptor.cpp.orig
+++ watchman/fs/FileDescriptor.cpp
@@ -7,6 +7,7 @@
 
 #include "watchman/fs/FileDescriptor.h"
 #include <folly/String.h>
+#include <cstring>
 #include <system_error>
 #include "watchman/fs/FSDetect.h"
 #include "watchman/fs/FileInformation.h"
@@ -19,6 +20,10 @@
 #include <sys/vnode.h> // @manual
 #endif
 
+#ifdef __FreeBSD__
+#include <sys/user.h> // @manual
+#endif
+
 #ifdef _WIN32
 #include <winioctl.h> // @manual
 #include <winsock2.h> // @manual
@@ -224,6 +229,29 @@ w_string FileDescriptor::getOpenedPath() const {
         errno, std::generic_category(), "fcntl for getOpenedPath");
   }
   return w_string(buf);
+#elif defined(__FreeBSD__)
+  // F_KINFO asks the kernel to resolve the path via its vnode name cache.
+  struct kinfo_file kif;
+  memset(&kif, 0, sizeof(kif));
+  kif.kf_structsize = sizeof(kif);
+
+  if (fcntl(fd_, F_KINFO, &kif) == -1) {
+    throw std::system_error(
+        errno, std::generic_category(), "fcntl F_KINFO for getOpenedPath");
+  }
+
+  if (kif.kf_path[0] == '\0') {
+    // kf_path is only populated from the name cache. A file just created
+    // via O_CREAT has no cache entry yet (NOCACHE is set for O_CREAT
+    // lookups) until some other lookup by name populates one, so kf_path
+    // can come back empty even though the fcntl call itself succeeded.
+    throw std::system_error(
+        ENOENT,
+        std::generic_category(),
+        "F_KINFO for getOpenedPath returned no path (freshly created file?)");
+  }
+
+  return w_string(kif.kf_path);
 #elif defined(__linux__) || defined(__sun)
   char procpath[1024];
 #if defined(__linux__)
@@ -325,8 +353,10 @@ w_string FileDescriptor::readSymbolicLink() const {
   std::string result;
   result.resize(st.st_size + 1, 0);
 
-#ifdef __linux__
-  // Linux 2.6.39 and later provide this interface
+#if defined(__linux__) || defined(O_PATH)
+  // Linux 2.6.39 and later, and any platform with O_PATH (which implies
+  // readlinkat() accepts an empty relative path to mean "this fd"),
+  // provide this interface.
   auto atlen = readlinkat(fd_, "", &result[0], result.size());
   if (atlen == int(result.size())) {
     // It's longer than we expected; TOCTOU detected!
@@ -338,8 +368,10 @@ w_string FileDescriptor::readSymbolicLink() const {
   if (atlen >= 0) {
     return w_string(result.data(), atlen);
   }
-  // if we get ENOTDIR back then we're probably on an older linux and
-  // should fall back to the technique used below.
+  // If we get ENOTDIR back then readlinkat()'s empty-path extension
+  // isn't actually supported here (eg: an older Linux, or an fd that
+  // wasn't opened with O_PATH) and we should fall back to the
+  // technique used below.
   if (errno != ENOTDIR) {
     throw std::system_error(
         errno, std::generic_category(), "readlinkat for readSymbolicLink");
