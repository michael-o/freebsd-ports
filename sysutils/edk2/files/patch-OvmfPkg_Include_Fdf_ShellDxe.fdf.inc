--- OvmfPkg/Include/Fdf/ShellDxe.fdf.inc.orig	2026-02-13 14:55:46.000000000 +0300
+++ OvmfPkg/Include/Fdf/ShellDxe.fdf.inc	2026-05-08 19:30:07.225022000 +0300
@@ -6,7 +6,7 @@
 # Built shell can be useful even when not included here, and is used in CI:
 # https://github.com/tianocore/edk2/commit/bc982869dd3e69ffd374fd968d378b5d954f66e8
 #
-!if $(BUILD_SHELL) == TRUE && $(SECURE_BOOT_ENABLE) == FALSE
+!if $(BUILD_SHELL) == TRUE
 
 !if $(TOOL_CHAIN_TAG) != "XCODE5"
 !if $(NETWORK_ENABLE) == TRUE
