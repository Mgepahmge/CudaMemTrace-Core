#ifndef CUDAMEMTRACECORE_FUNCTION_H
#define CUDAMEMTRACECORE_FUNCTION_H
#include <cudamemtrace/core/graph/Ids.h>
#include <cudamemtrace/core/support/SourceRange.h>
#include <vector>

namespace cudamemtrace::core {

    enum class FunctionKind {
        Normal,
        Constructor,
        Destructor,
        Operator,
        Lambda,
        Unknown
    };

    struct Function {
        FunctionId id;

        std::string name;
        std::string qualified_name;
        std::string signature;

        FunctionKind kind = FunctionKind::Normal;

        SourceRange source_range;

        bool is_definition = false;
        bool is_declaration_only = false;
        bool is_extern = false;
        bool is_template = false;

        std::vector<VariableId> parameters;
    };
}

#endif // CUDAMEMTRACECORE_FUNCTION_H
