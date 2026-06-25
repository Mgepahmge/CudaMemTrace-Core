#ifndef CUDAMEMTRACECORE_CALLBINDING_H
#define CUDAMEMTRACECORE_CALLBINDING_H
#include <cudamemtrace/core/graph/Ids.h>

namespace cudamemtrace::core {
    struct CallBinding {
        VariableId formal_parameter;
        SymbolicExprId actual_argument;
    };
}

#endif // CUDAMEMTRACECORE_CALLBINDING_H
