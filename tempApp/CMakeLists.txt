cmake_minimum_required(VERSION 3.16)
project(caseFeedback LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

add_library(caseFeedback
  src/test_lib.cc
)

target_include_directories(caseFeedback PUBLIC ${PROJECT_SOURCE_DIR}/include)
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_subdirectory(tests)
