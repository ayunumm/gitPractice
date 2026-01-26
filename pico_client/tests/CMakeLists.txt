add_executable(pico_client_test
  tests.cpp
)

target_link_libraries(pico_client_test
  PRIVATE
    pico_client_test_lib
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(pico_client_test)
