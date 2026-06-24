# CudaMemTrace Core

CudaMemTrace Core is a C++ static library for building and querying source-level CFG/ICFG models of CUDA/C++ programs with CUDA memory allocation/free annotations.

Core responsibilities:

1. Convert input source files into structured CFG/ICFG data.
2. Provide structured I/O for CFG/ICFG data.
3. Materialize one memory timeline from CFG/ICFG under caller-provided path constraints.

Path selection, command-line policy, reports, and visualization belong to `cudamemtrace-cli` and `cudamemtrace-ui`.

## Build

```bash
cmake -S . -B build -G Ninja \
  -DLLVM_DIR=/usr/lib/llvm-21/lib/cmake/llvm \
  -DClang_DIR=/usr/lib/llvm-21/lib/cmake/clang \
  -DCUDAMEMTRACE_CORE_BUILD_TESTS=ON \
  -DCUDAMEMTRACE_CORE_BUILD_EXAMPLES=ON

cmake --build build
ctest --test-dir build --output-on-failure
```

## Install

```bash
cmake --install build --prefix install
```

The exported target is:

```cmake
find_package(CudaMemTraceCore REQUIRED)
target_link_libraries(my_target PRIVATE CudaMemTrace::Core)
```

## Documentation

API documentation is generated with Doxygen. Install `doxygen` and optionally `graphviz`, then run:

```bash
./scripts/generate_docs.sh
```

The generated HTML documentation is written under the chosen build directory, for example `build/docs/docs/html/index.html`.
