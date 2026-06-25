#include <cudamemtrace/core/graph/FunctionCFG.h>
#include <cassert>

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
        auto [it, inserted] = map.try_emplace(id.value(), val);
        assert(inserted && "duplicate graph id");
        return it;
    }
    CFGBlockId FunctionCFG::addBlock(const CFGBlock& block) {
        addVal(block, block.id, blocks);
        return block.id;
    }
    CFGEdgeId FunctionCFG::addEdge(const CFGEdge& edge) {
        addVal(edge, edge.id, edges);

        if (auto* from_block = findBlock(edge.from)) {
            from_block->successor_edges.push_back(edge.id);
        }

        if (auto* to_block = findBlock(edge.to)) {
            to_block->predecessor_edges.push_back(edge.id);
        }

        return edge.id;
    }
} // namespace cudamemtrace::core
