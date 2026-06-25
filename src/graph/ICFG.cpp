#include <cudamemtrace/core/graph/ICFG.h>
#include <cassert>

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
        auto [it, inserted] = map.try_emplace(id.value(), val);
        assert(inserted && "duplicate graph id");
        return it;
    }

    ICFGNodeId ICFG::addNode(const ICFGNode& node) {
        addVal(node, node.id, nodes);
        return node.id;
    }
    ICFGEdgeId ICFG::addEdge(const ICFGEdge& edge) {
        addVal(edge, edge.id, edges);

        if (auto* from_node = findNode(edge.from)) {
            from_node->outgoing_edges.push_back(edge.id);
        }

        if (auto* to_node = findNode(edge.to)) {
            to_node->incoming_edges.push_back(edge.id);
        }

        return edge.id;
    }
} // namespace cudamemtrace::core
