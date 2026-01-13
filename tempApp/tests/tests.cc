#include <gtest/gtest.h>
#include "test_lib.hh"

TEST(caseFeedbackTest, add) {
  EXPECT_EQ(add(5, 5), 10);
  EXPECT_EQ(add(3, 1), 4);
}
