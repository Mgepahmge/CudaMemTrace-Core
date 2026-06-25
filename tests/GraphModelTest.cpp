#include <cudamemtrace/core/graph/FunctionCFG.h>
#include <cudamemtrace/core/graph/ICFG.h>
#include <cudamemtrace/core/graph/ProgramGraph.h>

#include <gtest/gtest.h>

#include <string>

namespace cudamemtrace::core {
namespace {

Function makeFunction(FunctionId id, const char* name) {
    Function function;
    function.id = id;
    function.name = name;
    function.qualified_name = name;
    function.signature = std::string("void ") + name + "()";
    function.is_definition = true;
    return function;
}

CFGBlock makeBlock(FunctionId function_id, CFGBlockId block_id, CFGBlockKind kind) {
    CFGBlock block;
    block.id = block_id;
    block.function_id = function_id;
    block.kind = kind;
    return block;
}

CFGEdge makeCFGEdge(
    FunctionId function_id,
    CFGEdgeId edge_id,
    CFGBlockId from,
    CFGBlockId to,
    CFGEdgeKind kind = CFGEdgeKind::Normal) {
    CFGEdge edge;
    edge.id = edge_id;
    edge.function_id = function_id;
    edge.from = from;
    edge.to = to;
    edge.kind = kind;
    return edge;
}

ICFGNode makeICFGNode(
    ICFGNodeId id,
    ICFGNodeKind kind,
    FunctionId function_id,
    CFGBlockId cfg_block_id = CFGBlockId{},
    CallSiteId call_site_id = CallSiteId{}) {
    ICFGNode node;
    node.id = id;
    node.kind = kind;
    node.function_id = function_id;
    if (cfg_block_id.isValid()) {
        node.cfg_block_id = cfg_block_id;
    }
    if (call_site_id.isValid()) {
        node.call_site_id = call_site_id;
    }
    return node;
}

ICFGEdge makeICFGEdge(
    ICFGEdgeId id,
    ICFGNodeId from,
    ICFGNodeId to,
    ICFGEdgeKind kind,
    CallSiteId call_site_id = CallSiteId{}) {
    ICFGEdge edge;
    edge.id = id;
    edge.from = from;
    edge.to = to;
    edge.kind = kind;
    if (call_site_id.isValid()) {
        edge.call_site_id = call_site_id;
    }
    return edge;
}

TEST(GraphModelTest, FunctionCFGAddEdgeUpdatesBlockAdjacency) {
    const FunctionId function_id{1};
    const CFGBlockId entry_id{10};
    const CFGBlockId body_id{11};
    const CFGBlockId exit_id{12};
    const CFGEdgeId entry_to_body_id{100};
    const CFGEdgeId body_to_exit_id{101};

    FunctionCFG cfg;
    cfg.function_id = function_id;
    cfg.entry_block = entry_id;
    cfg.exit_block = exit_id;

    cfg.addBlock(makeBlock(function_id, entry_id, CFGBlockKind::Entry));
    cfg.addBlock(makeBlock(function_id, body_id, CFGBlockKind::Normal));
    cfg.addBlock(makeBlock(function_id, exit_id, CFGBlockKind::Exit));

    cfg.addEdge(makeCFGEdge(function_id, entry_to_body_id, entry_id, body_id));
    cfg.addEdge(makeCFGEdge(function_id, body_to_exit_id, body_id, exit_id, CFGEdgeKind::Return));

    const auto* entry = cfg.findBlock(entry_id);
    const auto* body = cfg.findBlock(body_id);
    const auto* exit = cfg.findBlock(exit_id);

    ASSERT_NE(entry, nullptr);
    ASSERT_NE(body, nullptr);
    ASSERT_NE(exit, nullptr);

    ASSERT_EQ(entry->successor_edges.size(), 1U);
    EXPECT_EQ(entry->successor_edges.front(), entry_to_body_id);
    EXPECT_TRUE(entry->predecessor_edges.empty());

    ASSERT_EQ(body->predecessor_edges.size(), 1U);
    EXPECT_EQ(body->predecessor_edges.front(), entry_to_body_id);
    ASSERT_EQ(body->successor_edges.size(), 1U);
    EXPECT_EQ(body->successor_edges.front(), body_to_exit_id);

    ASSERT_EQ(exit->predecessor_edges.size(), 1U);
    EXPECT_EQ(exit->predecessor_edges.front(), body_to_exit_id);
    EXPECT_TRUE(exit->successor_edges.empty());

    const auto* edge = cfg.findEdge(body_to_exit_id);
    ASSERT_NE(edge, nullptr);
    EXPECT_EQ(edge->kind, CFGEdgeKind::Return);
}

TEST(GraphModelTest, ICFGAddEdgeUpdatesNodeAdjacency) {
    const FunctionId caller_function{1};
    const FunctionId callee_function{2};
    const CFGBlockId caller_block{10};
    const CallSiteId call_site_id{30};

    const ICFGNodeId caller_block_node_id{100};
    const ICFGNodeId call_site_node_id{101};
    const ICFGNodeId callee_entry_node_id{102};
    const ICFGNodeId callee_exit_node_id{103};
    const ICFGNodeId return_site_node_id{104};

    const ICFGEdgeId intra_to_call_id{200};
    const ICFGEdgeId call_edge_id{201};
    const ICFGEdgeId return_edge_id{202};

    ICFG icfg;
    icfg.addNode(makeICFGNode(caller_block_node_id, ICFGNodeKind::BasicBlock, caller_function, caller_block));
    icfg.addNode(makeICFGNode(call_site_node_id, ICFGNodeKind::CallSite, caller_function, caller_block, call_site_id));
    icfg.addNode(makeICFGNode(callee_entry_node_id, ICFGNodeKind::FunctionEntry, callee_function));
    icfg.addNode(makeICFGNode(callee_exit_node_id, ICFGNodeKind::FunctionExit, callee_function));
    icfg.addNode(makeICFGNode(return_site_node_id, ICFGNodeKind::ReturnSite, caller_function, caller_block, call_site_id));

    icfg.addEdge(makeICFGEdge(intra_to_call_id, caller_block_node_id, call_site_node_id, ICFGEdgeKind::Intra));
    icfg.addEdge(makeICFGEdge(call_edge_id, call_site_node_id, callee_entry_node_id, ICFGEdgeKind::Call, call_site_id));
    icfg.addEdge(makeICFGEdge(return_edge_id, callee_exit_node_id, return_site_node_id, ICFGEdgeKind::Return, call_site_id));

    const auto* caller_block_node = icfg.findNode(caller_block_node_id);
    const auto* call_site_node = icfg.findNode(call_site_node_id);
    const auto* callee_entry_node = icfg.findNode(callee_entry_node_id);
    const auto* callee_exit_node = icfg.findNode(callee_exit_node_id);
    const auto* return_site_node = icfg.findNode(return_site_node_id);

    ASSERT_NE(caller_block_node, nullptr);
    ASSERT_NE(call_site_node, nullptr);
    ASSERT_NE(callee_entry_node, nullptr);
    ASSERT_NE(callee_exit_node, nullptr);
    ASSERT_NE(return_site_node, nullptr);

    ASSERT_EQ(caller_block_node->outgoing_edges.size(), 1U);
    EXPECT_EQ(caller_block_node->outgoing_edges.front(), intra_to_call_id);

    ASSERT_EQ(call_site_node->incoming_edges.size(), 1U);
    EXPECT_EQ(call_site_node->incoming_edges.front(), intra_to_call_id);
    ASSERT_EQ(call_site_node->outgoing_edges.size(), 1U);
    EXPECT_EQ(call_site_node->outgoing_edges.front(), call_edge_id);

    ASSERT_EQ(callee_entry_node->incoming_edges.size(), 1U);
    EXPECT_EQ(callee_entry_node->incoming_edges.front(), call_edge_id);

    ASSERT_EQ(callee_exit_node->outgoing_edges.size(), 1U);
    EXPECT_EQ(callee_exit_node->outgoing_edges.front(), return_edge_id);

    ASSERT_EQ(return_site_node->incoming_edges.size(), 1U);
    EXPECT_EQ(return_site_node->incoming_edges.front(), return_edge_id);

    const auto* call_edge = icfg.findEdge(call_edge_id);
    ASSERT_NE(call_edge, nullptr);
    EXPECT_EQ(call_edge->kind, ICFGEdgeKind::Call);
    ASSERT_TRUE(call_edge->call_site_id.has_value());
    EXPECT_EQ(*call_edge->call_site_id, call_site_id);
}

TEST(GraphModelTest, ProgramGraphAddCallSiteUpdatesOwningCFGBlock) {
    const FunctionId foo_id{1};
    const FunctionId bar_id{2};
    const CFGBlockId foo_entry_id{10};
    const CFGBlockId foo_call_block_id{11};
    const CFGBlockId foo_exit_id{12};
    const CFGEdgeId entry_to_call_id{100};
    const CFGEdgeId call_to_exit_id{101};
    const CallSiteId call_site_id{200};

    ProgramGraph graph;
    graph.addFunction(makeFunction(foo_id, "foo"));
    graph.addFunction(makeFunction(bar_id, "bar"));

    FunctionCFG foo_cfg;
    foo_cfg.function_id = foo_id;
    foo_cfg.entry_block = foo_entry_id;
    foo_cfg.exit_block = foo_exit_id;
    foo_cfg.addBlock(makeBlock(foo_id, foo_entry_id, CFGBlockKind::Entry));
    foo_cfg.addBlock(makeBlock(foo_id, foo_call_block_id, CFGBlockKind::Call));
    foo_cfg.addBlock(makeBlock(foo_id, foo_exit_id, CFGBlockKind::Exit));
    foo_cfg.addEdge(makeCFGEdge(foo_id, entry_to_call_id, foo_entry_id, foo_call_block_id));
    foo_cfg.addEdge(makeCFGEdge(foo_id, call_to_exit_id, foo_call_block_id, foo_exit_id));

    graph.addCFG(foo_cfg);

    CallSite call_site;
    call_site.id = call_site_id;
    call_site.caller_function = foo_id;
    call_site.cfg_block = foo_call_block_id;
    call_site.kind = CallSiteKind::DirectCall;
    call_site.resolution = CallResolutionState::Resolved;
    call_site.callee_name = "bar";
    call_site.resolved_callee = bar_id;
    graph.addCallSite(call_site);

    const auto* stored_call_site = graph.findCallSite(call_site_id);
    ASSERT_NE(stored_call_site, nullptr);
    EXPECT_EQ(stored_call_site->caller_function, foo_id);
    ASSERT_TRUE(stored_call_site->resolved_callee.has_value());
    EXPECT_EQ(*stored_call_site->resolved_callee, bar_id);

    const auto* stored_cfg = graph.findCFG(foo_id);
    ASSERT_NE(stored_cfg, nullptr);

    const auto* call_block = stored_cfg->findBlock(foo_call_block_id);
    ASSERT_NE(call_block, nullptr);
    ASSERT_EQ(call_block->call_sites.size(), 1U);
    EXPECT_EQ(call_block->call_sites.front(), call_site_id);
}

#ifndef NDEBUG
TEST(GraphModelDeathTest, FunctionCFGAddEdgeRejectsMissingEndpoint) {
    const FunctionId function_id{1};
    const CFGBlockId entry_id{10};
    const CFGBlockId missing_id{99};
    const CFGEdgeId edge_id{100};

    FunctionCFG cfg;
    cfg.function_id = function_id;
    cfg.addBlock(makeBlock(function_id, entry_id, CFGBlockKind::Entry));

    EXPECT_DEATH(
        cfg.addEdge(makeCFGEdge(function_id, edge_id, entry_id, missing_id)),
        "CFG edge target block does not exist");
}

TEST(GraphModelDeathTest, ProgramGraphAddCallSiteRejectsMissingCFGBlock) {
    const FunctionId function_id{1};
    const CFGBlockId entry_id{10};
    const CFGBlockId missing_call_block_id{99};
    const CallSiteId call_site_id{100};

    ProgramGraph graph;
    graph.addFunction(makeFunction(function_id, "foo"));

    FunctionCFG cfg;
    cfg.function_id = function_id;
    cfg.entry_block = entry_id;
    cfg.exit_block = entry_id;
    cfg.addBlock(makeBlock(function_id, entry_id, CFGBlockKind::Entry));
    graph.addCFG(cfg);

    CallSite call_site;
    call_site.id = call_site_id;
    call_site.caller_function = function_id;
    call_site.cfg_block = missing_call_block_id;
    call_site.callee_name = "bar";

    EXPECT_DEATH(graph.addCallSite(call_site), "callsite CFG block does not exist");
}
#endif

} // namespace
} // namespace cudamemtrace::core
