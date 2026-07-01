--- MdeModulePkg/Universal/Console/TerminalDxe/TerminalConOut.c.orig	2026-05-08 05:42:59.000000000 +0300
+++ MdeModulePkg/Universal/Console/TerminalDxe/TerminalConOut.c	2026-06-04 20:39:46.510759000 +0300
@@ -487,8 +487,6 @@
   EFI_STATUS    Status;
   TERMINAL_DEV  *TerminalDevice;
   CHAR16        *String;
-  UINTN         Columns;
-  UINTN         Rows;
 
   //
   // Get Terminal device data structure pointer.
@@ -502,22 +500,8 @@
   //
   // Configure terminal string for the text mode to set.
   //
-  if (ModeNumber == 0) {
-    String = mSetModeString;
-  } else {
-    Columns = TerminalDevice->TerminalConsoleModeData[ModeNumber].Columns;
-    Rows    = TerminalDevice->TerminalConsoleModeData[ModeNumber].Rows;
-
-    mSetModeStringResize[RESIZE_ROW_OFFSET + 0]    = (CHAR16)('0' + (Rows / 100));
-    mSetModeStringResize[RESIZE_ROW_OFFSET + 1]    = (CHAR16)('0' + ((Rows % 100) / 10));
-    mSetModeStringResize[RESIZE_ROW_OFFSET + 2]    = (CHAR16)('0' + (Rows % 10));
-    mSetModeStringResize[RESIZE_COLUMN_OFFSET + 0] = (CHAR16)('0' + (Columns / 100));
-    mSetModeStringResize[RESIZE_COLUMN_OFFSET + 1] = (CHAR16)('0' + ((Columns % 100) / 10));
-    mSetModeStringResize[RESIZE_COLUMN_OFFSET + 2] = (CHAR16)('0' + (Columns % 10));
+  String = mSetModeString;
 
-    String = mSetModeStringResize;
-  }
-
   //
   // Set the current mode
   //
