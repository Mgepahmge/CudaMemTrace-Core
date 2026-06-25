#ifndef CUDAMEMTRACECORE_IDS_H
#define CUDAMEMTRACECORE_IDS_H
#include <cstdint>
#include <iosfwd>

namespace cudamemtrace::core {
    template <typename Tag>
    class Id {
    public:
        using valueType = std::uint64_t;

        constexpr Id() = default;
        explicit constexpr Id(const valueType value) : value_(value) {}

        constexpr valueType value() const { return value_; }

        constexpr bool isValid() const { return value_ != 0; }

        friend constexpr bool operator==(const Id& lhs, const Id& rhs) { return lhs.value_ == rhs.value_; }

        friend constexpr bool operator!=(const Id& lhs, const Id& rhs) { return lhs.value_ != rhs.value_; }

    private:
        valueType value_ = 0;
    };

    struct FunctionIdTag {};
    struct CFGBlockIdTag {};
    struct CFGEdgeIdTag {};
    struct ICFGNodeIdTag {};
    struct ICFGEdgeIdTag {};
    struct CallSiteIdTag {};
    struct VariableIdTag {};
    struct SymbolicExprIdTag {};
    struct MemoryOpIdTag {};
    struct MemoryObjectIdTag {};
    struct TypeIdTag {};
    struct SourceLocationIdTag {};

    using FunctionId = Id<FunctionIdTag>;
    using CFGBlockId = Id<CFGBlockIdTag>;
    using CFGEdgeId = Id<CFGEdgeIdTag>;
    using ICFGNodeId = Id<ICFGNodeIdTag>;
    using ICFGEdgeId = Id<ICFGEdgeIdTag>;
    using CallSiteId = Id<CallSiteIdTag>;
    using VariableId = Id<VariableIdTag>;
    using SymbolicExprId = Id<SymbolicExprIdTag>;
    using MemoryOpId = Id<MemoryOpIdTag>;
    using MemoryObjectId = Id<MemoryObjectIdTag>;
    using TypeId = Id<TypeIdTag>;
    using SourceLocationId = Id<SourceLocationIdTag>;
} // namespace cudamemtrace::core

#endif // CUDAMEMTRACECORE_IDS_H
