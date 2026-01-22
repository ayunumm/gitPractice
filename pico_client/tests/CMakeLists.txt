add_executable(caseFeedbackTests
  tests.cpp
)

target_link_libraries(caseFeedbackTests
  PRIVATE
    caseFeedback_lib
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(caseFeedbackTests)
