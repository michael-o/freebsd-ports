--- watchman/test/FileDescriptorTest.cpp.orig
+++ watchman/test/FileDescriptorTest.cpp
@@ -0,0 +1,168 @@
+/*
+ * Copyright (c) Meta Platforms, Inc. and affiliates.
+ *
+ * This source code is licensed under the MIT license found in the
+ * LICENSE file in the root directory of this source tree.
+ */
+
+#include "watchman/fs/FileDescriptor.h"
+
+#include <folly/portability/GTest.h>
+#include <folly/testing/TestUtil.h>
+#include <system_error>
+#include "watchman/fs/FileSystem.h"
+#include "watchman/watchman_string.h"
+
+#ifndef _WIN32
+#include <fcntl.h>
+#include <unistd.h>
+#endif
+
+using folly::test::TemporaryDirectory;
+using namespace watchman;
+
+namespace {
+
+#ifndef _WIN32
+
+class FileDescriptorTest : public ::testing::Test {
+ protected:
+  std::string path(std::string_view name) const {
+    return (tempDir_.path() / std::string{name}).string();
+  }
+
+  TemporaryDirectory tempDir_;
+};
+
+// Opening an existing file by path and resolving the fd back to a path
+// should round-trip to the same file.
+TEST_F(FileDescriptorTest, GetOpenedPath_ExistingFile_ResolvesToSamePath) {
+  const auto filePath = path("existing_file");
+  {
+    FileDescriptor fd(
+        open(filePath.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0600),
+        "create test file",
+        FileDescriptor::FDType::Unknown);
+  }
+
+  FileDescriptor fd(
+      open(filePath.c_str(), O_RDONLY),
+      "open test file",
+      FileDescriptor::FDType::Unknown);
+
+  auto resolved = fd.getOpenedPath();
+
+  struct stat viaOpened{};
+  struct stat viaOriginal{};
+  ASSERT_EQ(stat(resolved.c_str(), &viaOpened), 0);
+  ASSERT_EQ(stat(filePath.c_str(), &viaOriginal), 0);
+  EXPECT_EQ(viaOpened.st_dev, viaOriginal.st_dev);
+  EXPECT_EQ(viaOpened.st_ino, viaOriginal.st_ino);
+}
+
+// Opening a directory and resolving its fd should round-trip too.
+TEST_F(FileDescriptorTest, GetOpenedPath_Directory_ResolvesToSamePath) {
+  FileDescriptor fd(
+      open(tempDir_.path().string().c_str(), O_RDONLY | O_DIRECTORY),
+      "open test dir",
+      FileDescriptor::FDType::Unknown);
+
+  auto resolved = fd.getOpenedPath();
+
+  struct stat viaOpened{};
+  struct stat viaOriginal{};
+  ASSERT_EQ(stat(resolved.c_str(), &viaOpened), 0);
+  ASSERT_EQ(stat(tempDir_.path().string().c_str(), &viaOriginal), 0);
+  EXPECT_EQ(viaOpened.st_dev, viaOriginal.st_dev);
+  EXPECT_EQ(viaOpened.st_ino, viaOriginal.st_ino);
+}
+
+// openFileHandle() with default options (strictNameChecks=1) performs a
+// getOpenedPath() call internally to verify the canonical path. This must
+// succeed for an existing file looked up by name.
+TEST_F(FileDescriptorTest, OpenFileHandle_ExistingFile_StrictChecksSucceed) {
+  const auto filePath = path("strict_checked_file");
+  {
+    FileDescriptor fd(
+        open(filePath.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0600),
+        "create test file",
+        FileDescriptor::FDType::Unknown);
+  }
+
+  auto opts = OpenFileHandleOptions::queryFileInfo();
+  opts.strictNameChecks = true;
+  EXPECT_NO_THROW({ auto fd = openFileHandle(filePath.c_str(), opts); });
+}
+
+// openFileHandle() with opts.create set must not attempt the strict
+// canonical-path check, since there's no pre-existing canonical path for a
+// brand new file to diverge from. This is the guard added to
+// openFileHandle() in watchman/fs/FileSystem.cpp.
+TEST_F(FileDescriptorTest, OpenFileHandle_Create_SkipsStrictPathCheck) {
+  const auto filePath = path("freshly_created_file");
+
+  OpenFileHandleOptions opts;
+  opts.create = true;
+  opts.writeContents = true;
+  opts.strictNameChecks = true;
+
+  EXPECT_NO_THROW({ auto fd = openFileHandle(filePath.c_str(), opts); });
+}
+
+// realPath() on an existing, already-canonical file should return a path
+// that resolves back to the same file.
+TEST_F(FileDescriptorTest, RealPath_ExistingFile_ResolvesToSamePath) {
+  const auto filePath = path("real_path_file");
+  {
+    FileDescriptor fd(
+        open(filePath.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0600),
+        "create test file",
+        FileDescriptor::FDType::Unknown);
+  }
+
+  auto resolved = realPath(filePath.c_str());
+
+  struct stat viaResolved{};
+  struct stat viaOriginal{};
+  ASSERT_EQ(stat(resolved.c_str(), &viaResolved), 0);
+  ASSERT_EQ(stat(filePath.c_str(), &viaOriginal), 0);
+  EXPECT_EQ(viaResolved.st_dev, viaOriginal.st_dev);
+  EXPECT_EQ(viaResolved.st_ino, viaOriginal.st_ino);
+}
+
+// realPath() must follow symlinks and return the target's canonical path,
+// not the symlink's own path.
+TEST_F(FileDescriptorTest, RealPath_Symlink_ResolvesToTarget) {
+  const auto targetPath = path("real_path_target");
+  const auto linkPath = path("real_path_link");
+  {
+    FileDescriptor fd(
+        open(targetPath.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0600),
+        "create target file",
+        FileDescriptor::FDType::Unknown);
+  }
+  ASSERT_EQ(symlink(targetPath.c_str(), linkPath.c_str()), 0);
+
+  auto resolved = realPath(linkPath.c_str());
+
+  struct stat viaResolved{};
+  struct stat viaTarget{};
+  ASSERT_EQ(stat(resolved.c_str(), &viaResolved), 0);
+  ASSERT_EQ(stat(targetPath.c_str(), &viaTarget), 0);
+  EXPECT_EQ(viaResolved.st_dev, viaTarget.st_dev);
+  EXPECT_EQ(viaResolved.st_ino, viaTarget.st_ino);
+  // The resolved path must not be the symlink's own path: following it is
+  // the whole point of realPath().
+  EXPECT_NE(resolved, w_string(linkPath.c_str()));
+}
+
+// realPath() on a path that does not exist must throw rather than return
+// a bogus or partially-resolved path.
+TEST_F(FileDescriptorTest, RealPath_NonExistentPath_Throws) {
+  const auto missingPath = path("does_not_exist");
+  EXPECT_THROW(realPath(missingPath.c_str()), std::system_error);
+}
+
+#endif // !_WIN32
+
+} // namespace
