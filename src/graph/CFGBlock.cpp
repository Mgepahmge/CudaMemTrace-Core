#include <cudamemtrace/core/graph/CFGBlock.h>

namespace cudamemtrace::core {
    bool CFGBlock::isEntry() const {
        return kind == CFGBlockKind::Entry;
    }
    bool CFGBlock::isExit() const  {
        return kind == CFGBlockKind::Exit;
    }
} // namespace cudamemtrace::core
