#include "gtest/gtest.h"
#include <PiecewiseConstantParameter.h>

TEST(PiecewiseConstantParameterTest, IntegralTest) {
	PiecewiseConstantParameter parameter{ { {0.0, 10.0}, {3.0, 30.0}, {5.0, 50.0}, {10.0, 100.0} } };
	EXPECT_NEAR(parameter.integral(1.0, 10.0), 330.0, 0.0001);
}

TEST(PiecewiseConstantParameterTest, IntegralTest_Right) {
	PiecewiseConstantParameter parameter{ { {0.0, 10.0}, {3.0, 30.0}, {5.0, 50.0}, {10.0, 100.0} } };
	EXPECT_NEAR(parameter.integral(5.0, 20.0), 1250.0, 0.0001);
}

TEST(PiecewiseConstantParameterTest, IntegralSquareTest) {
	PiecewiseConstantParameter parameter{ { {0.0, 10.0}, {3.0, 30.0}, {5.0, 50.0}, {10.0, 100.0} } };
	EXPECT_NEAR(parameter.integralSquare(3.0, 10.0), 14300.0, 0.0001);
}

TEST(PiecewiseConstantParameterTest, GetValueTest) {
	PiecewiseConstantParameter parameter{ { {0.0, 10.0}, {3.0, 30.0}, {5.0, 50.0}, {10.0, 100.0} } };
	EXPECT_NEAR(parameter[5.5], 50.0, 0.0001);
}

TEST(PiecewiseConstantParameterTest, GetValueTest_Exact) {
	PiecewiseConstantParameter parameter{ { {0.0, 10.0}, {3.0, 30.0}, {5.0547, 50.0}, {10.0, 100.0} } };
	EXPECT_NEAR(parameter[5.0547], 50.0, 0.0001);
}

TEST(PiecewiseConstantParameterTest, GetValueTest_Right) {
	PiecewiseConstantParameter parameter{ { {0.0, 10.0}, {3.0, 30.0}, {5.0, 50.0}, {10.0, 100.0} } };
	EXPECT_NEAR(parameter[15.0], 100.0, 0.0001);
}