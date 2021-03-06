#include <Actual360.h>
#include <Actual365.h>
#include <Thirty360Isda.h>
#include "gtest/gtest.h"

using namespace qff_a;
using boost::gregorian::date;

TEST(Actual360Test, CalculateYearFractionTest) {
  const Actual360 day_counter{};
  const auto result =
      day_counter.CalculateYearFraction(date(2018, 2, 10), date(2018, 12, 30));

  EXPECT_NEAR(result, 0.89722, 0.0001);
}

TEST(Actual365Test, CalculateYearFractionTest) {
  const Actual365 day_counter{};
  const auto result =
      day_counter.CalculateYearFraction(date(2018, 2, 10), date(2018, 12, 30));

  EXPECT_NEAR(result, 0.88493, 0.0001);
}

TEST(Thirty360IsdaTest, CalculateYearFractionTest) {
  const Thirty360Isda day_counter{};
  const auto result =
      day_counter.CalculateYearFraction(date(2011, 8, 31), date(2012, 2, 29));

  EXPECT_NEAR(result, 0.5, 0.0001);
}

TEST(Thirty360IsdaTest, CalculateYearFractionTest_Maturity) {
  const Thirty360Isda day_counter{};
  const auto result = day_counter.CalculateYearFraction(
      date(2011, 8, 31), date(2012, 2, 29), true);

  EXPECT_NEAR(result, 0.497222222, 0.0001);
}