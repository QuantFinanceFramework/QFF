#include <Actual365.h>
#include <FlatZeroRateCurve.h>
#include "gtest/gtest.h"

using namespace qff_a;
using boost::gregorian::date;

TEST(FlatZeroCurveTest, GetDiscountFactor) {
  const FlatZeroRateCurve<double> zero{date{2019, 1, 1}, "Std", Actual365(), 0.02};
  const auto actual = zero.GetDiscountFactor(date{2020, 1, 3});
  EXPECT_NEAR(actual, 0.980091260159824, 0.0000001);
}