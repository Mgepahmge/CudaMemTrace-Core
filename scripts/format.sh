#!/usr/bin/env bash
set -euo pipefail

CLANG_FORMAT=${CLANG_FORMAT:-clang-format}
find include src tests examples -type f \( -name '*.h' -o -name '*.hh' -o -name '*.hpp' -o -name '*.hxx' -o -name '*.cc' -o -name '*.cpp' -o -name '*.cxx' \) -print0 | xargs -0 "${CLANG_FORMAT}" -i
