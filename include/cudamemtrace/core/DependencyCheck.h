#pragma once

#include <string>

namespace cudamemtrace::core {

    struct DependencyInfo {
        std::string llvm_version;
        std::string clang_version;
        std::string json_status;

        [[nodiscard]] std::string summary() const;
    };

    [[nodiscard]] DependencyInfo collectDependencyInfo();
    [[nodiscard]] std::string dependencyInfoJson();

} // namespace cudamemtrace::core
