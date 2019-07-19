#include <Actual360.h>
#include <Actual365.h>
#include "gtest/gtest.h"

using namespace qff;
TEST(Actual360Test, calculateYearFractionTest) {
  Actual360 dayCounter{};
  auto result =
      dayCounter.calculateYearFraction(date(2018, 2, 10), date(2018, 12, 30));

  EXPECT_NEAR(result, 0.89722, 0.0001);
}

TEST(Actual365Test, calculateYearFractionTest) {
  Actual365 dayCounter{};
  auto result =
      dayCounter.calculateYearFraction(date(2018, 2, 10), date(2018, 12, 30));

  EXPECT_NEAR(result, 0.88493, 0.0001);
}