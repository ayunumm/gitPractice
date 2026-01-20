add_executable(caseFeedbackTests
  tests.c
)

target_link_libraries(caseFeedbackTests
  PRIVATE
    caseFeedback
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(caseFeedbackTests)
