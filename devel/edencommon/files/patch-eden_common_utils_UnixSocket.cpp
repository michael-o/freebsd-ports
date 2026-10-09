--- eden/common/utils/UnixSocket.cpp.orig
+++ eden/common/utils/UnixSocket.cpp
@@ -21,7 +21,7 @@
 #include <folly/portability/SysUio.h>
 #include <algorithm>
 #include <new>
-#ifdef __APPLE__
+#if defined(__APPLE__) || defined(__FreeBSD__)
 #include <sys/ucred.h> // @manual
 #endif
 #include "eden/common/utils/Bug.h"
