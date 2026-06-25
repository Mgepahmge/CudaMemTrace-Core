#ifndef CUDAMEMTRACECORE_SOURCELOCATION_H
#define CUDAMEMTRACECORE_SOURCELOCATION_H
#include <string>
#include <cstdint>

namespace cudamemtrace::core {
    struct SourceLocation {
        std::string file;
        std::uint32_t line = 0;
        std::uint32_t column = 0;
    };
}

#endif // CUDAMEMTRACECORE_SOURCELOCATION_H
