#include <cudamemtrace/core/DependencyCheck.h>

#include <clang/Basic/Version.h>
#include <llvm/Config/llvm-config.h>
#include <llvm/Support/raw_ostream.h>
#include <nlohmann/json.hpp>

#include <string>

namespace cudamemtrace::core {

    std::string DependencyInfo::summary() const {
        std::string out;
        llvm::raw_string_ostream stream(out);
        stream << "LLVM " << llvm_version << ", " << clang_version << ", JSON " << json_status;
        return stream.str();
    }

    DependencyInfo collectDependencyInfo() {
        nlohmann::json probe;
        probe["nlohmann_json"] = true;

        return DependencyInfo{
            LLVM_VERSION_STRING,
            clang::getClangFullVersion(),
            probe.value("nlohmann_json", false) ? "available" : "unavailable",
        };
    }

    std::string dependencyInfoJson() {
        const auto info = collectDependencyInfo();
        const nlohmann::json payload = {
            {"llvm_version", info.llvm_version},
            {"clang_version", info.clang_version},
            {"json_status", info.json_status},
            {"summary", info.summary()},
        };
        return payload.dump(2);
    }

} // namespace cudamemtrace::core
