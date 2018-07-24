#include "gtest/gtest.h"
#include <BasicDayCounter.h>

TEST(BasicDayCounterTest, countDayBetweenTest) {

	BasicDayCounter time{ date(2002,12,30), date(2002,12,10) };
	auto result = time.countDayBetween();

	EXPECT_NEAR(result, 20, 0.0001);

}

TEST(BasicDayCounterTest, calculateYearFractionTest) {

	BasicDayCounter time{ date(2002,12,30), date(2002,12,10) };
	auto result = time.calculateYearFraction();

	EXPECT_NEAR(result, 0.05479452, 0.0001);

}