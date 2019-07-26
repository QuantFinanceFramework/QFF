#include <Actual360.h>
#include <Actual365.h>
#include "gtest/gtest.h"

using namespace qff;

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