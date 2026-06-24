#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${1:-${PROJECT_ROOT}/build/docs}"
shift || true

cmake -S "${PROJECT_ROOT}" -B "${BUILD_DIR}" -G Ninja \
  -DLLVM_DIR="${LLVM_DIR:-/usr/lib/llvm-21/lib/cmake/llvm}" \
  -DClang_DIR="${Clang_DIR:-/usr/lib/llvm-21/lib/cmake/clang}" \
  -DCUDAMEMTRACE_CORE_BUILD_TESTS=OFF \
  -DCUDAMEMTRACE_CORE_BUILD_EXAMPLES=OFF \
  -DCUDAMEMTRACE_CORE_BUILD_DOCS=ON \
  "$@"

cmake --build "${BUILD_DIR}" --target docs

echo "Doxygen HTML documentation generated at: ${BUILD_DIR}/docs/html/index.html"
