--- build/fbcode_builder/CMake/RustStaticLibrary.cmake.orig
+++ build/fbcode_builder/CMake/RustStaticLibrary.cmake
@@ -58,7 +58,7 @@
   )
 endif()
 
-find_program(CARGO_COMMAND cargo REQUIRED)
+find_program(CARGO_COMMAND cargo)
 
 # Cargo is a build system in itself, and thus will try to take advantage of all
 # the cores on the system. Unfortunately, this conflicts with Ninja, since it
