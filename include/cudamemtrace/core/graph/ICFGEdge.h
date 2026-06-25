#ifndef CUDAMEMTRACECORE_ICFGEDGE_H
#define CUDAMEMTRACECORE_ICFGEDGE_H
#include <cudamemtrace/core/graph/Ids.h>
#include <cudamemtrace/core/support/SourceRange.h>
#include <optional>

namespace cudamemtrace::core {
    enum class ICFGEdgeKind {
        Intra,
        Call,
        Return,
        ExternalCall,
        UnresolvedCall,
        Unknown
    };

    struct ICFGEdge {
        ICFGEdgeId id;

        ICFGNodeId from;
        ICFGNodeId to;

        ICFGEdgeKind kind = ICFGEdgeKind::Unknown;

        std::optional<CallSiteId> call_site_id;
        std::optional<SymbolicExprId> condition_expr;

        std::string label;

        SourceRange source_range;
    };
}

#endif // CUDAMEMTRACECORE_ICFGEDGE_H
