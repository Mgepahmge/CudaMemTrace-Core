# CudaMemTrace Core Documentation

This directory contains design notes and generated API documentation configuration for CudaMemTrace Core.

Current engineering scope:

1. Build annotated CFG/ICFG models from CUDA/C++ source files.
2. Read and write structured CFG/ICFG data.
3. Generate one structured memory timeline from caller-provided path constraints.

Doxygen configuration lives in `docs/doxygen/`. Use:

```bash
./scripts/generate_docs.sh
```

or configure CMake with `CUDAMEMTRACE_CORE_BUILD_DOCS=ON` and build the `docs` target.
