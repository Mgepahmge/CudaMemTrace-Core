#include <cudamemtrace/core/DependencyCheck.h>

#include <gtest/gtest.h>

#include <string>

TEST(CudaMemTraceCoreDependencyCheck, ReportsAvailableDependencies) {
    const auto info = cudamemtrace::core::collectDependencyInfo();

    EXPECT_FALSE(info.llvm_version.empty());
    EXPECT_FALSE(info.clang_version.empty());
    EXPECT_EQ(info.json_status, "available");
    EXPECT_NE(info.summary().find("LLVM"), std::string::npos);
}

TEST(CudaMemTraceCoreDependencyCheck, EmitsJsonPayload) {
    const auto payload = cudamemtrace::core::dependencyInfoJson();

    EXPECT_NE(payload.find("llvm_version"), std::string::npos);
    EXPECT_NE(payload.find("clang_version"), std::string::npos);
    EXPECT_NE(payload.find("json_status"), std::string::npos);
}
