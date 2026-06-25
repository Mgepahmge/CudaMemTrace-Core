#ifndef CUDAMEMTRACECORE_ICFGNODE_H
#define CUDAMEMTRACECORE_ICFGNODE_H
#include <cudamemtrace/core/graph/Ids.h>
#include <cudamemtrace/core/support/SourceRange.h>
#include <optional>
#include <vector>

namespace cudamemtrace::core {
    enum class ICFGNodeKind {
        FunctionEntry,
        FunctionExit,
        BasicBlock,
        CallSite,
        ReturnSite,
        ExternalFunction,
        Unknown
    };

    struct ICFGNode {
        ICFGNodeId id;
        ICFGNodeKind kind = ICFGNodeKind::Unknown;

        FunctionId function_id;

        std::optional<CFGBlockId> cfg_block_id;
        std::optional<CallSiteId> call_site_id;

        SourceRange source_range;

        std::vector<ICFGEdgeId> incoming_edges;
        std::vector<ICFGEdgeId> outgoing_edges;
    };
}

#endif // CUDAMEMTRACECORE_ICFGNODE_H
