find_package(GTest REQUIRED)
include(GoogleTest)

file(GLOB_RECURSE CUDAMEMTRACE_CORE_TEST_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

if(CUDAMEMTRACE_CORE_TEST_SOURCES)
  add_executable(CudaMemTraceCoreTests ${CUDAMEMTRACE_CORE_TEST_SOURCES})
  target_link_libraries(CudaMemTraceCoreTests
    PRIVATE
      CudaMemTrace::Core
      GTest::gtest_main
  )
  gtest_discover_tests(CudaMemTraceCoreTests)
endif()
