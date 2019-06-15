#include "gtest/gtest.h"
#include <ConstantParameter.h>

TEST(ConstantParameterTest, IntegralTest) {
	ConstantParameter parameter{ 10.0 };
	EXPECT_NEAR(parameter.integral(1.0, 100.0), 990.0, 0.0001);
}

TEST(ConstantParameterTest, IntegralSquareTest) {
	ConstantParameter parameter{ 10.0 };
	EXPECT_NEAR(parameter.integralSquare(1.0, 100.0), 9900.0, 0.0001);
}

TEST(ConstantParameterTest, GetValueTest) {
	ConstantParameter parameter{ 10.0 };
	EXPECT_NEAR(parameter[5], 10.0, 0.0001);
}