file(GLOB_RECURSE CUDAMEMTRACE_CORE_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

file(GLOB_RECURSE CUDAMEMTRACE_CORE_HEADERS CONFIGURE_DEPENDS
  "${PROJECT_SOURCE_DIR}/include/*.h"
  "${PROJECT_SOURCE_DIR}/include/*.hh"
  "${PROJECT_SOURCE_DIR}/include/*.hpp"
  "${PROJECT_SOURCE_DIR}/include/*.hxx"
)

if(NOT CUDAMEMTRACE_CORE_SOURCES)
  message(FATAL_ERROR "No source files were found under src/")
endif()

add_library(CudaMemTraceCore STATIC
  ${CUDAMEMTRACE_CORE_SOURCES}
  ${CUDAMEMTRACE_CORE_HEADERS}
)

add_library(CudaMemTrace::Core ALIAS CudaMemTraceCore)

set_target_properties(CudaMemTraceCore PROPERTIES
  OUTPUT_NAME cudamemtrace-core
  POSITION_INDEPENDENT_CODE ON
  EXPORT_NAME Core
)

target_compile_features(CudaMemTraceCore PUBLIC cxx_std_17)

target_include_directories(CudaMemTraceCore
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
)

target_compile_definitions(CudaMemTraceCore
  PRIVATE
    ${LLVM_DEFINITIONS}
)

target_link_libraries(CudaMemTraceCore
  PRIVATE
    ${CUDAMEMTRACE_LLVM_LIBS}
    ${CUDAMEMTRACE_CLANG_LIBS}
    nlohmann_json::nlohmann_json
)
