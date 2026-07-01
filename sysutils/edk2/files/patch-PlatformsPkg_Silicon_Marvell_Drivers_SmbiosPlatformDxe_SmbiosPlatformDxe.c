--- PlatformsPkg/Silicon/Marvell/Drivers/SmbiosPlatformDxe/SmbiosPlatformDxe.c.orig	2026-03-27 11:50:02 UTC
+++ PlatformsPkg/Silicon/Marvell/Drivers/SmbiosPlatformDxe/SmbiosPlatformDxe.c
@@ -227,8 +227,8 @@ STATIC SMBIOS_TABLE_TYPE7 mArmadaDefaultType7_a72_l1i 
   CacheTypeInstruction,    //instruction cache
   CacheAssociativityOther, //three way
   // SMBIOS 3.1.0 fields
-  48,    //48k I-cache max
-  48,    //48k installed
+  {48,0},    //48k I-cache max
+  {48,0}    //48k installed
 };
 
 STATIC SMBIOS_TABLE_TYPE7 mArmadaDefaultType7_a72_l1d = {
@@ -248,8 +248,8 @@ STATIC SMBIOS_TABLE_TYPE7 mArmadaDefaultType7_a72_l1d 
   CacheTypeData,           //data cache
   CacheAssociativity2Way,  //two way
   // SMBIOS 3.1.0 fields
-  32,    //32k D-cache max
-  32,    //32k installed
+  {32,0},    //32k D-cache max
+  {32,0}    //32k installed
 };
 
 STATIC SMBIOS_TABLE_TYPE7 mArmadaDefaultType7_a72_l2 = {
@@ -269,8 +269,8 @@ STATIC SMBIOS_TABLE_TYPE7 mArmadaDefaultType7_a72_l2 =
   CacheTypeUnified,        //instruction cache
   CacheAssociativity16Way, //16 way associative
   // SMBIOS 3.1.0 fields
-  512,   //512k D-cache max
-  512,   //512k installed
+  {512,0},   //512k D-cache max
+  {512,0}   //512k installed
 };
 
 STATIC SMBIOS_TABLE_TYPE7 mArmadaDefaultType7_l3 = {
@@ -290,8 +290,8 @@ STATIC SMBIOS_TABLE_TYPE7 mArmadaDefaultType7_l3 = {
   CacheTypeUnified,        //instruction cache
   CacheAssociativity8Way,  //8 way associative
   // SMBIOS 3.1.0 fields
-  1024,  //1M cache max
-  1024,  //1M installed
+  {1024,0},  //1M cache max
+  {1024,0}  //1M installed
 };
 
 STATIC CONST CHAR8 *mArmadaDefaultType7Strings[] = {
