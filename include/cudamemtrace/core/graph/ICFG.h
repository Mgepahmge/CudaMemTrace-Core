#ifndef CUDAMEMTRACECORE_ICFG_H
#define CUDAMEMTRACECORE_ICFG_H
#include <cudamemtrace/core/graph/ICFGNode.h>
#include <cudamemtrace/core/graph/ICFGEdge.h>
#include <unordered_map>

namespace cudamemtrace::core {
    struct ICFG {
        std::unordered_map<ICFGNodeId::valueType, ICFGNode> nodes;
        std::unordered_map<ICFGEdgeId::valueType, ICFGEdge> edges;

        ICFGNodeId entry_node;
        ICFGNodeId exit_node;

        ICFGNode* findNode(ICFGNodeId id);
        const ICFGNode* findNode(ICFGNodeId id) const;

        ICFGEdge* findEdge(ICFGEdgeId id);
        const ICFGEdge* findEdge(ICFGEdgeId id) const;

        ICFGNodeId addNode(const  ICFGNode& node);
        ICFGEdgeId addEdge(const ICFGEdge& edge);
    };
}

#endif // CUDAMEMTRACECORE_ICFG_H
