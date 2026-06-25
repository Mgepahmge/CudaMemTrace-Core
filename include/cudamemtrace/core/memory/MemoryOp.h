#ifndef CUDAMEMTRACECORE_MEMORYOP_H
#define CUDAMEMTRACECORE_MEMORYOP_H
#include <cudamemtrace/core/graph/Ids.h>

namespace cudamemtrace::core {

    struct MemoryOp {
        MemoryOpId id;
    };

}

#endif // CUDAMEMTRACECORE_MEMORYOP_H
