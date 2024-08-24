include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  test_algos
  test_fenwick_tree.cpp
  test_lazy_segment_tree.cpp
  test_lazy_segment_tree_range.cpp
  test_modint.cpp
  test_rmp.cpp
  test_segment_tree.cpp
)

target_include_directories(test_algos PRIVATE ${PROJECT_SOURCE_DIR}/algos)
target_link_libraries(test_algos GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_algos)
