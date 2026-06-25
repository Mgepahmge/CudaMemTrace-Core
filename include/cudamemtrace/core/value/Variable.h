#ifndef CUDAMEMTRACECORE_VARIABLE_H
#define CUDAMEMTRACECORE_VARIABLE_H
#include <cudamemtrace/core/graph/Ids.h>

namespace cudamemtrace::core {

    struct Variable {
        VariableId id;
    };

}

#endif // CUDAMEMTRACECORE_VARIABLE_H
