#ifndef CUDAMEMTRACECORE_FUNCTIONCFG_H
#define CUDAMEMTRACECORE_FUNCTIONCFG_H
#include <cudamemtrace/core/graph/CFGBlock.h>
#include <cudamemtrace/core/graph/CFGEdge.h>
#include <unordered_map>

namespace cudamemtrace::core {
    struct FunctionCFG {
        FunctionId function_id;

        CFGBlockId entry_block;
        CFGBlockId exit_block;

        std::unordered_map<CFGBlockId::valueType, CFGBlock> blocks;
        std::unordered_map<CFGEdgeId::valueType, CFGEdge> edges;

        CFGBlock* findBlock(CFGBlockId id);
        const CFGBlock* findBlock(CFGBlockId id) const;

        CFGEdge* findEdge(CFGEdgeId id);
        const CFGEdge* findEdge(CFGEdgeId id) const;

        CFGBlockId addBlock(const CFGBlock& block);
        CFGEdgeId addEdge(const CFGEdge& edge);
    };
}

#endif // CUDAMEMTRACECORE_FUNCTIONCFG_H
