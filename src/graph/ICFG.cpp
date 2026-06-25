#include <cudamemtrace/core/graph/ICFG.h>

namespace cudamemtrace::core {
    ICFGNode* ICFG::findNode(const ICFGNodeId id) {
        const auto it = nodes.find(id.value());
        if (it == nodes.end()) {
            return nullptr;
        }
        return &it->second;
    }
    const ICFGNode* ICFG::findNode(const ICFGNodeId id) const {
        const auto it = nodes.find(id.value());
        if (it == nodes.end()) {
            return nullptr;
        }
        return &it->second;
    }
    ICFGEdge* ICFG::findEdge(const ICFGEdgeId id) {
        const auto it = edges.find(id.value());
        if (it == edges.end()) {
            return nullptr;
        }
        return &it->second;
    }
    const ICFGEdge* ICFG::findEdge(const ICFGEdgeId id) const {
        const auto it = edges.find(id.value());
        if (it == edges.end()) {
            return nullptr;
        }
        return &it->second;
    }

    template<typename Id, typename Val>
    auto addVal(const Val& val, const Id id, std::unordered_map<typename Id::valueType, Val>& map) {
        if (auto [it, inserted] = map.try_emplace(id.value(), val); inserted) {
            return it;
        }
        return map.find(id.value());
    }

    ICFGNodeId ICFG::addNode(const ICFGNode& node) {
        addVal(node, node.id, nodes);
        return node.id;
    }
    ICFGEdgeId ICFG::addEdge(const ICFGEdge& edge) {
        addVal(edge, edge.id, edges);
        return edge.id;
    }
} // namespace cudamemtrace::core
