#ifndef CUDAMEMTRACECORE_CALLSITE_H
#define CUDAMEMTRACECORE_CALLSITE_H
#include <cudamemtrace/core/call/CallBinding.h>
#include <cudamemtrace/core/support/SourceRange.h>
#include <optional>
#include <vector>

namespace cudamemtrace::core {
    enum class CallSiteKind {
        DirectCall,
        MemberCall,
        ConstructorCall,
        DestructorCall,
        OperatorCall,
        FunctionPointerCall,
        VirtualCall,
        LambdaCall,
        Unknown
    };

    enum class CallResolutionState {
        Resolved,
        Unresolved,
        Ambiguous,
        External
    };

    struct CallSite {
        CallSiteId id;

        FunctionId caller_function;
        CFGBlockId cfg_block;

        CallSiteKind kind = CallSiteKind::DirectCall;
        CallResolutionState resolution = CallResolutionState::Unresolved;

        std::string callee_name;
        std::optional<FunctionId> resolved_callee;

        std::vector<SymbolicExprId> actual_arguments;
        std::vector<CallBinding> bindings;

        std::optional<SymbolicExprId> return_value_expr;

        SourceRange source_range;
    };
}

#endif // CUDAMEMTRACECORE_CALLSITE_H
