#include <ConstantParameter.h>
#include "gtest/gtest.h"

using namespace qff;

TEST(ConstantParameterTest, IntegralTest) {
  const ConstantParameter parameter{10.0};
  EXPECT_NEAR(parameter.Integral(1.0, 100.0), 990.0, 0.0001);
}

TEST(ConstantParameterTest, IntegralSquareTest) {
  const ConstantParameter parameter{10.0};
  EXPECT_NEAR(parameter.IntegralSquare(1.0, 100.0), 9900.0, 0.0001);
}

TEST(ConstantParameterTest, GetValueTest) {
  const ConstantParameter parameter{10.0};
  EXPECT_NEAR(parameter[5], 10.0, 0.0001);
}