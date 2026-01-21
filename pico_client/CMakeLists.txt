cmake_minimum_required(VERSION 3.16)
project(caseFeedback LANGUAGES C CXX)

cmake_policy(SET CMP0135 NEW)

include(CTest)
enable_testing()

add_library(caseFeedback_lib
  src/test_lib.c
)

target_include_directories(caseFeedback_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(caseFeedback
  src/main.c
)

target_link_libraries(caseFeedback PRIVATE caseFeedback_lib)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(tests)
