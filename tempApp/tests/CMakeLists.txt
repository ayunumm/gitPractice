add_executable(caseFeedbackTests
  tests.cc
)

target_link_libraries(caseFeedbackTests
  PRIVATE
    caseFeedback
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(caseFeedbackTests)
