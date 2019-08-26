#include <NewYorkCalendar.h>
#include "gtest/gtest.h"

using namespace qff;
using boost::gregorian::date;

class NewYorkCalendarTestFixture : public ::testing::TestWithParam<date> {
 protected:
  NewYorkCalendar nyc_;
};

TEST_F(NewYorkCalendarTestFixture, IsBusinessDayTest_Weekednd) {
  EXPECT_FALSE(nyc_.IsBusinessDay(date(2019, 4, 20)));
}

TEST_F(NewYorkCalendarTestFixture, IsBusinessDayTest_Holiday) {
  EXPECT_FALSE(nyc_.IsBusinessDay(date(2019, 5, 27)));
}

TEST_P(NewYorkCalendarTestFixture, IsHolidayTest_Holidays) {
  const auto holiday = GetParam();
  EXPECT_TRUE(nyc_.IsHoliday(holiday));
}

INSTANTIATE_TEST_CASE_P(
    Holidays, NewYorkCalendarTestFixture,
    ::testing::Values(date(2018, 1, 1), date(2018, 1, 15), date(2018, 2, 19),
                      date(2018, 5, 28), date(2018, 7, 4), date(2018, 9, 3),
                      date(2018, 10, 8), date(2018, 11, 12), date(2018, 11, 22),
                      date(2018, 12, 25), date(2019, 1, 1), date(2019, 1, 21),
                      date(2019, 2, 18), date(2019, 5, 27), date(2019, 7, 4),
                      date(2019, 9, 2), date(2019, 10, 14), date(2019, 11, 11),
                      date(2019, 11, 28), date(2019, 12, 25), date(2020, 1, 1),
                      date(2020, 1, 20), date(2020, 2, 17), date(2020, 5, 25),
                      date(2020, 7, 3), date(2020, 9, 7), date(2020, 10, 12),
                      date(2020, 11, 11), date(2020, 11, 26),
                      date(2020, 12, 25), date(2021, 1, 1), date(2021, 1, 18),
                      date(2021, 2, 15), date(2021, 5, 31), date(2021, 7, 5),
                      date(2021, 9, 6), date(2021, 10, 11), date(2021, 11, 11),
                      date(2021, 11, 25), date(2021, 12, 24),
                      date(2021, 12, 31)));
