#ifndef CUDAMEMTRACECORE_CFGEDGE_H
#define CUDAMEMTRACECORE_CFGEDGE_H
#include <cudamemtrace/core/graph/Ids.h>
#include <cudamemtrace/core/support/SourceRange.h>
#include <optional>

namespace cudamemtrace::core {
    enum class CFGEdgeKind {
        Normal,

        TrueBranch,
        FalseBranch,

        SwitchCase,
        SwitchDefault,

        LoopBody,
        LoopExit,
        LoopBack,

        Break,
        Continue,
        Return,

        Exceptional,
        Unreachable,
        Unknown
    };

    struct CFGEdge {
        CFGEdgeId id;
        FunctionId function_id;

        CFGBlockId from;
        CFGBlockId to;

        CFGEdgeKind kind = CFGEdgeKind::Normal;

        std::optional<SymbolicExprId> condition_expr;

        std::string label;

        SourceRange source_range;
    };
}

#endif // CUDAMEMTRACECORE_CFGEDGE_H
