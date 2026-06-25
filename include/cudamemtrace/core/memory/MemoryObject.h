#ifndef CUDAMEMTRACECORE_MEMORYOBJECT_H
#define CUDAMEMTRACECORE_MEMORYOBJECT_H
#include <cudamemtrace/core/graph/Ids.h>

namespace cudamemtrace::core {

    struct MemoryObject {
        MemoryObjectId id;
    };

}

#endif // CUDAMEMTRACECORE_MEMORYOBJECT_H
