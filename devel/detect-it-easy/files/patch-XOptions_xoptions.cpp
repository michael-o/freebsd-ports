--- XOptions/xoptions.cpp.orig
+++ XOptions/xoptions.cpp
@@ -1116,7 +1116,7 @@
 #ifdef Q_OS_WIN
         nFontSize = 9;
 #endif
-#ifdef Q_OS_LINUX
+#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
         nFontSize = 11;
 #endif
     }
@@ -1126,6 +1126,9 @@
 #endif
 #ifdef Q_OS_LINUX
     fontResult = QFont("Ubuntu", nFontSize);
+#endif
+#ifdef Q_OS_FREEBSD
+    fontResult = QFont("Sans Serif", nFontSize);
 #endif
 #ifdef Q_OS_MACOS
     fontResult = QFont(".AppleSystemUIFont", nFontSize);
@@ -1146,7 +1149,7 @@
 #ifdef Q_OS_WIN
         nFontSize = 10;
 #endif
-#ifdef Q_OS_LINUX
+#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
         nFontSize = 10;
 #endif
     }
@@ -1165,7 +1168,7 @@
         sFontFamily = "Consolas";
     }
 #endif
-#ifdef Q_OS_LINUX
+#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
     if (listFamilies.contains("DejaVu Sans Mono")) {
         sFontFamily = "DejaVu Sans Mono";
     } else if (listFamilies.contains("Liberation Mono")) {
@@ -2232,7 +2235,7 @@
         if (sApplicationDirPath.contains("/usr/local/bin")) {
             QString sPrefix = sApplicationDirPath.section("/usr/local/bin", 0, 0);
 
-            sResult += sPrefix + QString("/usr/local/lib/%1").arg(sApplicationName);
+            sResult += sPrefix + QString("/usr/local/share/%1").arg(sApplicationName);
 
             if (QDir(sResult).exists()) {
                 bResult = true;
@@ -2304,7 +2307,14 @@
 #endif
 #ifdef Q_OS_FREEBSD
     if (!bResult) {
-        sResult = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).at(1) + QDir::separator() + sApplicationName;
+        QStringList dataLocations = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation);
+        for (const QString &location : dataLocations) {
+            QString candidate = location + QDir::separator() + sApplicationName;
+            if (QDir(candidate).exists()) {
+                sResult = candidate;
+                break;
+            }
+        }
 
         if (QDir(sResult).exists()) {
             bResult = true;
@@ -2386,7 +2396,7 @@
             if (sApplicationDirPath.contains("/usr/local/bin")) {
                 _sPathName = sPathName;
                 QString sPrefix = sApplicationDirPath.section("/usr/local/bin", 0, 0);
-                QString sPath = sPrefix + QString("/usr/local/lib/%1").arg(sApplicationName);
+                QString sPath = sPrefix + QString("/usr/local/share/%1").arg(sApplicationName);
 
                 _sPathName = _sPathName.replace("$data", sPath);
 
@@ -2435,7 +2445,7 @@
 
         if (!bSuccess) {
              _sPathName = sPathName;
-            QString sPath = QString("/usr/local/lib/%1").arg(sApplicationName);
+            QString sPath = QString("/usr/local/share/%1").arg(sApplicationName);
 
             _sPathName = _sPathName.replace("$data", sPath);
 
