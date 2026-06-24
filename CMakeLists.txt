cmake_minimum_required(VERSION 3.20)

project(CudaMemTraceCore
  VERSION 0.1.0
  DESCRIPTION "Static core library for CFG/ICFG-based CUDA memory allocation/free timelines"
  LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

option(CUDAMEMTRACE_CORE_BUILD_TESTS "Build CudaMemTrace Core tests" ON)
option(CUDAMEMTRACE_CORE_BUILD_EXAMPLES "Build CudaMemTrace Core examples" ON)
option(CUDAMEMTRACE_CORE_BUILD_DOCS "Build CudaMemTrace Core Doxygen documentation" OFF)

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
find_package(nlohmann_json REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Using ClangConfig.cmake in: ${Clang_DIR}")

if(COMMAND llvm_map_components_to_libnames)
  llvm_map_components_to_libnames(CUDAMEMTRACE_LLVM_LIBS support)
else()
  message(FATAL_ERROR "LLVM CMake function llvm_map_components_to_libnames is not available")
endif()

set(CUDAMEMTRACE_CLANG_LIBS)
if(TARGET clang-cpp)
  list(APPEND CUDAMEMTRACE_CLANG_LIBS clang-cpp)
else()
  foreach(lib IN ITEMS
      clangTooling
      clangFrontend
      clangSerialization
      clangDriver
      clangParse
      clangSema
      clangAnalysis
      clangAST
      clangLex
      clangBasic)
    if(TARGET ${lib})
      list(APPEND CUDAMEMTRACE_CLANG_LIBS ${lib})
    endif()
  endforeach()
endif()

if(NOT CUDAMEMTRACE_CLANG_LIBS)
  message(FATAL_ERROR "No usable Clang CMake targets were found")
endif()

add_subdirectory(src)

if(CUDAMEMTRACE_CORE_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if(CUDAMEMTRACE_CORE_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

if(CUDAMEMTRACE_CORE_BUILD_DOCS)
  add_subdirectory(docs)
endif()

install(TARGETS CudaMemTraceCore
  EXPORT CudaMemTraceCoreTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING
    PATTERN "*.h"
    PATTERN "*.hh"
    PATTERN "*.hpp"
    PATTERN "*.hxx"
)

install(DIRECTORY schemas/
  DESTINATION ${CMAKE_INSTALL_DATADIR}/cudamemtrace-core/schemas
  OPTIONAL
)

install(EXPORT CudaMemTraceCoreTargets
  FILE CudaMemTraceCoreTargets.cmake
  NAMESPACE CudaMemTrace::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CudaMemTraceCore
)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CudaMemTraceCoreConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/CudaMemTraceCoreConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CudaMemTraceCore
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/CudaMemTraceCoreConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/CudaMemTraceCoreConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/CudaMemTraceCoreConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CudaMemTraceCore
)
