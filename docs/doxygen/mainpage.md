# CudaMemTrace Core API Documentation

CudaMemTrace Core is a C++ static library for building and querying source-level CFG/ICFG models of CUDA/C++ programs with CUDA memory allocation/free annotations.

## Core Responsibilities

1. Convert input source files into structured CFG/ICFG data.
2. Provide structured I/O for CFG/ICFG data.
3. Materialize one structured memory timeline from CFG/ICFG under caller-provided path constraints.

Core does not choose analysis policies, render timelines, or provide command-line/user-interface behavior. Those responsibilities belong to `cudamemtrace-cli` and `cudamemtrace-ui`.

## Public Headers

The public C++ API is installed from `include/cudamemtrace/core`.

## Generated Documentation

Build the `docs` target from CMake, or run `scripts/generate_docs.sh` after configuring the project with Doxygen available.
