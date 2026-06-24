file(GLOB_RECURSE CUDAMEMTRACE_CORE_EXAMPLE_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

foreach(example_source IN LISTS CUDAMEMTRACE_CORE_EXAMPLE_SOURCES)
  file(RELATIVE_PATH example_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${example_source}")
  string(REPLACE "/" "_" example_target_suffix "${example_rel}")
  string(REGEX REPLACE "\.[^.]*$" "" example_target_suffix "${example_target_suffix}")
  set(example_target "cudamemtrace_core_example_${example_target_suffix}")

  add_executable(${example_target} ${example_source})
  target_link_libraries(${example_target} PRIVATE CudaMemTrace::Core)
endforeach()
