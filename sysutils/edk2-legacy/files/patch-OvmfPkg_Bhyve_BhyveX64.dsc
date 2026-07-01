--- OvmfPkg/Bhyve/BhyveX64.dsc.orig	2023-08-25 04:54:50.000000000 +0300
+++ OvmfPkg/Bhyve/BhyveX64.dsc	2026-06-08 21:18:18.499012000 +0300
@@ -186,7 +186,7 @@
 !endif
 
   ResetSystemLib|OvmfPkg/Library/ResetSystemLib/BaseResetSystemLibBhyve.inf
-  LocalApicLib|UefiCpuPkg/Library/BaseXApicLib/BaseXApicLib.inf
+  LocalApicLib|UefiCpuPkg/Library/BaseXApicX2ApicLib/BaseXApicX2ApicLib.inf
   IoApicLib|PcAtChipsetPkg/Library/BaseIoApicLib/BaseIoApicLib.inf
   DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
 
@@ -539,7 +539,7 @@
   gUefiOvmfPkgTokenSpaceGuid.PcdPciMmio64Base|0x0
   gUefiOvmfPkgTokenSpaceGuid.PcdPciMmio64Size|0x800000000
 
-  gEfiMdePkgTokenSpaceGuid.PcdPlatformBootTimeOut|0
+  gEfiMdePkgTokenSpaceGuid.PcdPlatformBootTimeOut|1
 
   # Set video resolution for text setup.
   gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|640
