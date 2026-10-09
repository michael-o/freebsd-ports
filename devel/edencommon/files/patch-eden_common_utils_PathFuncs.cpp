--- eden/common/utils/PathFuncs.cpp.orig
+++ eden/common/utils/PathFuncs.cpp
@@ -22,6 +22,12 @@
 #include <mach-o/dyld.h> // @manual
 #endif
 
+#ifdef __FreeBSD__
+#include <sys/sysctl.h> // @manual
+#include <sys/types.h> // @manual
+#include <climits>
+#endif
+
 using folly::Expected;
 
 namespace facebook::eden {
@@ -406,6 +412,14 @@
   auto execPath = wideToMultibyteString<std::string>(
       std::wstring_view(buf.data(), static_cast<size_t>(res)));
   return normalizeBestEffort(execPath);
+#elif defined(__FreeBSD__)
+  int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1};
+  std::array<char, PATH_MAX> buf;
+  size_t size = buf.size();
+  folly::checkUnixError(
+      sysctl(mib, 4, buf.data(), &size, nullptr, 0),
+      "failed to read KERN_PROC_PATHNAME via sysctl");
+  return canonicalPath(std::string_view(buf.data(), size - 1));
 #else
 #error executablePath not implemented
 #endif
