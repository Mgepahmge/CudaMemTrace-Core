#!/usr/bin/env bash
set -euo pipefail

cmake --preset ubuntu-llvm21-debug
cmake --build --preset ubuntu-llvm21-debug
ctest --preset ubuntu-llvm21-debug
