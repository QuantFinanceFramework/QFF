#include <PiecewiseConstantParameter.h>
#include "gtest/gtest.h"

using namespace qff;

TEST(PiecewiseConstantParameterTest, IntegralTest) {
  PiecewiseConstantParameter parameter{
      {{0.0, 10.0}, {3.0, 30.0}, {5.0, 50.0}, {10.0, 100.0}}};
  EXPECT_NEAR(parameter.Integral(1.0, 10.0), 330.0, 0.0001);
}

TEST(PiecewiseConstantParameterTest, IntegralTest_Right) {
  PiecewiseConstantParameter parameter{
      {{0.0, 10.0}, {3.0, 30.0}, {5.0, 50.0}, {10.0, 100.0}}};
  EXPECT_NEAR(parameter.Integral(5.0, 20.0), 1250.0, 0.0001);
}

TEST(PiecewiseConstantParameterTest, IntegralSquareTest) {
  PiecewiseConstantParameter parameter{{{0.0, 0.0077154},
                                        {5.01918, 0.00705787},
                                        {8.01918, 0.00678679},
                                        {10.0219, 0.00542237},
                                        {11.0219, 0.00518465},
                                        {12.0219, 0.00433031},
                                        {13.0247, 0.00402051}}};
  EXPECT_NEAR(parameter.IntegralSquare(0.0, 10.0), 0.00053945690435152,
              0.00001);
}

TEST(PiecewiseConstantParameterTest, GetValueTest) {
  PiecewiseConstantParameter parameter{
      {{0.0, 10.0}, {3.0, 30.0}, {5.0, 50.0}, {10.0, 100.0}}};
  EXPECT_NEAR(parameter[5.5], 50.0, 0.0001);
}

TEST(PiecewiseConstantParameterTest, GetValueTest_Exact) {
  PiecewiseConstantParameter parameter{
      {{0.0, 10.0}, {3.0, 30.0}, {5.0547, 50.0}, {10.0, 100.0}}};
  EXPECT_NEAR(parameter[5.0547], 50.0, 0.0001);
}

TEST(PiecewiseConstantParameterTest, GetValueTest_Right) {
  PiecewiseConstantParameter parameter{
      {{0.0, 10.0}, {3.0, 30.0}, {5.0, 50.0}, {10.0, 100.0}}};
  EXPECT_NEAR(parameter[15.0], 100.0, 0.0001);
}