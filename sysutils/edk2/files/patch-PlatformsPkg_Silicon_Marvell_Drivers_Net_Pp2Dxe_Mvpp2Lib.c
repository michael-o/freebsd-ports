--- PlatformsPkg/Silicon/Marvell/Drivers/Net/Pp2Dxe/Mvpp2Lib.c.orig	2026-04-02 15:16:38.226832000 +0300
+++ PlatformsPkg/Silicon/Marvell/Drivers/Net/Pp2Dxe/Mvpp2Lib.c	2026-04-02 15:17:21.825386000 +0300
@@ -568,10 +568,6 @@
 
   if (Start > End) {
     Mvpp2SwapVariables (Start, End);
-  }
-
-  if (End >= MVPP2_PRS_TCAM_SRAM_SIZE) {
-    End = MVPP2_PRS_TCAM_SRAM_SIZE - 1;
   }
 
   for (Tid = Start; Tid <= End; Tid++) {
