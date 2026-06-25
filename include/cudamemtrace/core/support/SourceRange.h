#ifndef CUDAMEMTRACECORE_SOURCERANGE_H
#define CUDAMEMTRACECORE_SOURCERANGE_H
#include <cudamemtrace/core/support/SourceLoaction.h>

namespace cudamemtrace::core {
    struct SourceRange {
        SourceLocation begin;
        SourceLocation end;
    };
}

#endif // CUDAMEMTRACECORE_SOURCERANGE_H
