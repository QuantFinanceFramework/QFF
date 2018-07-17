#include "gtest/gtest.h"
#include <DayCounter.h>

TEST(DayCounterTest, calculateTest) {

	DayCounter time{ date(2002,12,30), date(2002,12,10) };
	auto result = time.calculate();

	EXPECT_NEAR(result, 20, 0.0001);

}

TEST(DayCounterTest, calculateYearFractionTest) {

	DayCounter time{ date(2002,12,30), date(2002,12,10) };
	auto result = time.calculateYearFraction();

	EXPECT_NEAR(result, 0.05479, 0.0001);

}