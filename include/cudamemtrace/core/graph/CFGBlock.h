#ifndef CUDAMEMTRACECORE_CFGBLOCK_H
#define CUDAMEMTRACECORE_CFGBLOCK_H
#include <cudamemtrace/core/graph/Ids.h>
#include <cudamemtrace/core/support/SourceRange.h>
#include <vector>

namespace cudamemtrace::core {
    enum class CFGBlockKind {
        Entry,
        Exit,
        Normal,
        Call,
        Return,
        Unreachable,
        Unknown
    };

    struct CFGBlock {
        CFGBlockId id;
        FunctionId function_id;

        CFGBlockKind kind = CFGBlockKind::Normal;

        SourceRange source_range;

        std::vector<CFGEdgeId> predecessor_edges;
        std::vector<CFGEdgeId> successor_edges;

        std::vector<CallSiteId> call_sites;

        std::vector<MemoryOpId> memory_ops;
        std::vector<SymbolicExprId> condition_exprs;
        std::vector<VariableId> referenced_variables;

        bool isEntry() const;

        bool isExit() const;
    };
}

#endif // CUDAMEMTRACECORE_CFGBLOCK_H
