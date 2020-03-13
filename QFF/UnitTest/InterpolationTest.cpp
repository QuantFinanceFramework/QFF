#include <Interpolation.h>
#include "gtest/gtest.h"
#include <map>

using namespace qff_a;

class InterpolationTestFixture : public ::testing::Test {
 protected:
  double query_{3.0};
  std::map<double, double> data_{{1.0, 10.0}, {2.5, 30.0}, {4.0, 55.5}, {15.0, 105.5}};

};

TEST_F(InterpolationTestFixture, LinearInterpol) {
  EXPECT_NEAR(LinearInterpol(query_, data_), 38.5, 0.0001);
}

TEST_F(InterpolationTestFixture, LogLinearInterpol) {
  EXPECT_NEAR(LogLinearInterpol(query_, data_), 36.8280307857645, 0.0001);
}

TEST_F(InterpolationTestFixture, LinearExtrapol) {
  EXPECT_NEAR(LinearExtrapol(20.0, data_), 128.227272727273, 0.0001);
}

TEST_F(InterpolationTestFixture, LogLinearExtrapol) {
  EXPECT_NEAR(LogLinearExtrapol(20.0, data_), 141.270740523057, 0.0001);
}

TEST_F(InterpolationTestFixture, ConstantExtrapol) {
  EXPECT_NEAR(ConstantExtrapol(20.0, data_), 105.5, 0.0001);
}


