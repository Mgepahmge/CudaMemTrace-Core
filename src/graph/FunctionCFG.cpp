#include <cudamemtrace/core/graph/FunctionCFG.h>

namespace cudamemtrace::core {
    CFGBlock* FunctionCFG::findBlock(const CFGBlockId id) {
        const auto it = blocks.find(id.value());
        if (it == blocks.end()) {
            return nullptr;
        }
        return &it->second;
    }
    const CFGBlock* FunctionCFG::findBlock(const CFGBlockId id) const {
        const auto it = blocks.find(id.value());
        if (it == blocks.end()) {
            return nullptr;
        }
        return &it->second;
    }
    CFGEdge* FunctionCFG::findEdge(const CFGEdgeId id) {
        const auto it = edges.find(id.value());
        if (it == edges.end()) {
            return nullptr;
        }
        return &it->second;
    }
    const CFGEdge* FunctionCFG::findEdge(const CFGEdgeId id) const {
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
    CFGBlockId FunctionCFG::addBlock(const CFGBlock& block) {
        addVal(block, block.id, blocks);
        return block.id;
    }
    CFGEdgeId FunctionCFG::addEdge(const CFGEdge& edge) {
        addVal(edge, edge.id, edges);
        return edge.id;
    }
} // namespace cudamemtrace::core
