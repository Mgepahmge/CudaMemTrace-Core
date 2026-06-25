#include <cudamemtrace/core/graph/ProgramGraph.h>
#include <cassert>

namespace cudamemtrace::core {
    template <typename Id, typename Val>
    Val* findVal(const Id id, std::unordered_map<typename Id::valueType, Val>& map) {
        const auto it = map.find(id.value());
        if (it == map.end()) {
            return nullptr;
        }
        return &it->second;
    }

    template <typename Id, typename Val>
    const Val* findVal(const Id id, const std::unordered_map<typename Id::valueType, Val>& map) {
        const auto it = map.find(id.value());
        if (it == map.end()) {
            return nullptr;
        }
        return &it->second;
    }

    Function* ProgramGraph::findFunction(const FunctionId id) {
        return findVal<FunctionId, Function>(id, functions);
    }
    const Function* ProgramGraph::findFunction(const FunctionId id) const {
        return findVal<FunctionId, Function>(id, functions);
    }
    FunctionCFG* ProgramGraph::findCFG(const FunctionId function_id) {
        return findVal<FunctionId, FunctionCFG>(function_id, cfgs);
    }
    const FunctionCFG* ProgramGraph::findCFG(const FunctionId function_id) const {
        return findVal<FunctionId, FunctionCFG>(function_id, cfgs);
    }
    CallSite* ProgramGraph::findCallSite(const CallSiteId id) {
        return findVal<CallSiteId, CallSite>(id, call_sites);
    }
    const CallSite* ProgramGraph::findCallSite(const CallSiteId id) const {
        return findVal<CallSiteId, CallSite>(id, call_sites);
    }
    Variable* ProgramGraph::findVariable(const VariableId id) {
        return findVal<VariableId, Variable>(id, variables);
    }
    const Variable* ProgramGraph::findVariable(const VariableId id) const {
        return findVal<VariableId, Variable>(id, variables);
    }
    SymbolicExpr* ProgramGraph::findSymbolicExpr(const SymbolicExprId id) {
        return findVal<SymbolicExprId, SymbolicExpr>(id, symbolic_exprs);
    }
    const SymbolicExpr* ProgramGraph::findSymbolicExpr(const SymbolicExprId id) const {
        return findVal<SymbolicExprId, SymbolicExpr>(id, symbolic_exprs);
    }
    MemoryOp* ProgramGraph::findMemoryOp(const MemoryOpId id) {
        return findVal<MemoryOpId, MemoryOp>(id, memory_ops);
    }
    const MemoryOp* ProgramGraph::findMemoryOp(const MemoryOpId id) const {
        return findVal<MemoryOpId, MemoryOp>(id, memory_ops);
    }
    MemoryObject* ProgramGraph::findMemoryObject(const MemoryObjectId id) {
        return findVal<MemoryObjectId, MemoryObject>(id, memory_objects);
    }
    const MemoryObject* ProgramGraph::findMemoryObject(const MemoryObjectId id) const {
        return findVal<MemoryObjectId, MemoryObject>(id, memory_objects);
    }

    template<typename Id, typename Val>
    auto addVal(const Val& val, const Id id, std::unordered_map<typename Id::valueType, Val>& map) {
        auto [it, inserted] = map.try_emplace(id.value(), val);
        assert(inserted && "duplicate graph id");
        return it;
    }

    FunctionId ProgramGraph::addFunction(const Function& function) {
        addVal(function, function.id, functions);
        return function.id;
    }
    FunctionCFG& ProgramGraph::addCFG(const FunctionCFG& cfg) {
        auto it = addVal(cfg, cfg.function_id, cfgs);
        return it->second;
    }
    CallSiteId ProgramGraph::addCallSite(const CallSite& call_site) {
        addVal(call_site, call_site.id, call_sites);
        return call_site.id;
    }
    VariableId ProgramGraph::addVariable(const Variable& variable) {
        addVal(variable, variable.id, variables);
        return variable.id;
    }
    SymbolicExprId ProgramGraph::addSymbolicExpr(const SymbolicExpr& symbolic_expr) {
        addVal(symbolic_expr, symbolic_expr.id, symbolic_exprs);
        return symbolic_expr.id;
    }
    MemoryOpId ProgramGraph::addMemoryOp(const MemoryOp& memory_op) {
        addVal(memory_op, memory_op.id, memory_ops);
        return memory_op.id;
    }
    MemoryObjectId ProgramGraph::addMemoryObject(const MemoryObject& memory_object) {
        addVal(memory_object, memory_object.id, memory_objects);
        return memory_object.id;
    }
} // namespace cudamemtrace::core
