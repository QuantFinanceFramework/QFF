#include <LondonCalendar.h>
#include "gtest/gtest.h"

using namespace qff;

class LondonCalendarTestFixture : public ::testing::TestWithParam<date> {
 protected:
  LondonCalendar lon_;
};

TEST_F(LondonCalendarTestFixture, IsBusinessDayTest_Weekednd) {
  EXPECT_FALSE(lon_.IsBusinessDay(date(2019, 4, 20)));
}

TEST_F(LondonCalendarTestFixture, IsBusinessDayTest_Holiday) {
  EXPECT_FALSE(lon_.IsBusinessDay(date(2019, 4, 19)));
}

TEST_P(LondonCalendarTestFixture, IsHolidayTest_Holidays) {
	const auto holiday = GetParam();
  EXPECT_TRUE(lon_.IsHoliday(holiday));
}

INSTANTIATE_TEST_CASE_P(
    Holidays, LondonCalendarTestFixture,
    ::testing::Values(date(2018, 1, 1), date(2018, 3, 30), date(2018, 4, 2),
                      date(2018, 5, 7), date(2018, 5, 28), date(2018, 8, 27),
                      date(2018, 12, 25), date(2018, 12, 26), date(2019, 1, 1),
                      date(2019, 4, 19), date(2019, 4, 22), date(2019, 5, 6),
                      date(2019, 5, 27), date(2019, 8, 26), date(2019, 12, 25),
                      date(2019, 12, 26), date(2020, 1, 1), date(2020, 4, 10),
                      date(2020, 4, 13), date(2020, 5, 8), date(2020, 5, 25),
                      date(2020, 8, 31), date(2020, 12, 25), date(2020, 12, 28),
                      date(2021, 1, 1)));
