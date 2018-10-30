#include "gtest/gtest.h"
#include <Actual365DayCounter.h>

TEST(Actual365DayCounterTest, countDayBetweenTest) {

	Actual365DayCounter dayCounter{};
	auto result = dayCounter.countDayBetween(date(2002, 12, 10), date(2002, 12, 30));

	EXPECT_NEAR(result, 20, 0.0001);

}

TEST(Actual365DayCounterTest, calculateYearFractionTest) {

	Actual365DayCounter dayCounter{};
	auto result = dayCounter.calculateYearFraction(date(2002, 12, 10), date(2002, 12, 30));

	EXPECT_NEAR(result, 0.05479452, 0.0001);

}