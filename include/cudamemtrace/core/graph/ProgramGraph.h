#ifndef CUDAMEMTRACECORE_PROGARAMGRAPH_H
#define CUDAMEMTRACECORE_PROGARAMGRAPH_H
#include <cudamemtrace/core/graph/Function.h>
#include <cudamemtrace/core/graph/FunctionCFG.h>
#include <cudamemtrace/core/graph/ICFG.h>
#include <cudamemtrace/core/call/CallSite.h>
#include <cudamemtrace/core/value/Variable.h>
#include <cudamemtrace/core/value/SymbolicExpr.h>
#include <cudamemtrace/core/memory/MemoryOp.h>
#include <cudamemtrace/core/memory/MemoryObject.h>

namespace cudamemtrace::core {
    struct ProgramGraph {
        std::string schema_version = "0.1.0";

        std::unordered_map<FunctionId::valueType, Function> functions;
        std::unordered_map<FunctionId::valueType, FunctionCFG> cfgs;
        std::unordered_map<CallSiteId::valueType, CallSite> call_sites;
        std::unordered_map<VariableId::valueType, Variable> variables;
        std::unordered_map<SymbolicExprId::valueType, SymbolicExpr> symbolic_exprs;
        std::unordered_map<MemoryOpId::valueType, MemoryOp> memory_ops;
        std::unordered_map<MemoryObjectId::valueType, MemoryObject> memory_objects;

        ICFG icfg;

        Function* findFunction(FunctionId id);
        const Function* findFunction(FunctionId id) const;

        FunctionCFG* findCFG(FunctionId function_id);
        const FunctionCFG* findCFG(FunctionId function_id) const;

        CallSite* findCallSite(CallSiteId id);
        const CallSite* findCallSite(CallSiteId id) const;

        Variable* findVariable(VariableId id);
        const Variable* findVariable(VariableId id) const;

        SymbolicExpr* findSymbolicExpr(SymbolicExprId id);
        const SymbolicExpr* findSymbolicExpr(SymbolicExprId id) const;

        MemoryOp* findMemoryOp(MemoryOpId id);
        const MemoryOp* findMemoryOp(MemoryOpId id) const;

        MemoryObject* findMemoryObject(MemoryObjectId id);
        const MemoryObject* findMemoryObject(MemoryObjectId id) const;

        FunctionId addFunction(const Function& function);
        FunctionCFG& addCFG(const FunctionCFG& cfg);
        CallSiteId addCallSite(const CallSite& call_site);
        VariableId addVariable(const Variable& variable);
        SymbolicExprId addSymbolicExpr(const SymbolicExpr& symbolic_expr);
        MemoryOpId addMemoryOp(const MemoryOp& memory_op);
        MemoryObjectId addMemoryObject(const MemoryObject& memory_object);
    };
}

#endif // CUDAMEMTRACECORE_PROGARAMGRAPH_H
