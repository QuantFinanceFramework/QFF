#include <Actual365.h>
#include <FlatZeroCurve.h>
#include "gtest/gtest.h"

using namespace qff;
using boost::gregorian::date;

TEST(FlatZeroCurveTest, GetDiscountFactor) {
  const FlatZeroCurve zero{date{2019, 1, 1}, 0.02, Actual365()};
  const auto actual = zero.GetDiscountFactor(date{2020, 1, 3});
  EXPECT_NEAR(actual, 0.980091260159824, 0.0000001);
}