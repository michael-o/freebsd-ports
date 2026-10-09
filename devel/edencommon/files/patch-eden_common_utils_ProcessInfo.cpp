--- eden/common/utils/ProcessInfo.cpp.orig
+++ eden/common/utils/ProcessInfo.cpp
@@ -39,6 +39,12 @@
 #include <sys/sysctl.h> // @manual
 #endif
 
+#ifdef __FreeBSD__
+#include <sys/sysctl.h> // @manual
+#include <sys/types.h> // @manual
+#include <sys/user.h> // @manual
+#endif
+
 #ifndef _WIN32
 #include <pwd.h>
 #endif
@@ -180,6 +186,19 @@
       : pid(pid), ppid(ppid), uid(uid) {}
 
   static std::optional<StatusInfo> create(pid_t pid) {
+#ifdef __FreeBSD__
+    // FreeBSD's procfs, when mounted at all, doesn't use Linux's
+    // /proc/<pid>/status key-value format. Query the kernel directly
+    // instead via the KERN_PROC_PID sysctl.
+    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PID, pid};
+    struct kinfo_proc kp;
+    size_t len = sizeof(kp);
+    if (sysctl(mib, 4, &kp, &len, nullptr, 0) == -1 || len != sizeof(kp)) {
+      XLOGF(DBG4, "Failed to read kinfo_proc for pid: {}", pid);
+      return std::nullopt;
+    }
+    return StatusInfo(pid, kp.ki_ppid, kp.ki_ruid);
+#else
     pid_t ppid;
     uid_t uid;
 
@@ -202,6 +221,7 @@
     }
     XLOGF(DBG4, "Failed to read status for pid: {}", pid);
     return std::nullopt;
+#endif
   }
 
   template <typename T>
