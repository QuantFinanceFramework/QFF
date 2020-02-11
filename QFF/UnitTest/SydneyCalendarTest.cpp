#include <SydneyCalendar.h>
#include "gtest/gtest.h"

using namespace qff;
using boost::gregorian::date;

class SydneyCalendarTestFixture : public ::testing::TestWithParam<date> {
 protected:
  SydneyCalendar syd_;
};

TEST_F(SydneyCalendarTestFixture, isBusinessDayTest_Weekednd) {
  EXPECT_FALSE(syd_.IsBusinessDay(date(2019, 4, 20)));
}

TEST_F(SydneyCalendarTestFixture, isBusinessDayTest_Holiday) {
  EXPECT_FALSE(syd_.IsBusinessDay(date(2019, 4, 19)));
}

TEST_F(SydneyCalendarTestFixture, isBusinessDayTest_MondayAfterAnzac) {
  EXPECT_TRUE(syd_.IsBusinessDay(date(2021, 4, 26)));
}

TEST_P(SydneyCalendarTestFixture, isHolidayTest_Holidays) {
  const auto holiday = GetParam();
  EXPECT_TRUE(syd_.IsHoliday(holiday));
}

INSTANTIATE_TEST_CASE_P(
    Holidays, SydneyCalendarTestFixture,
    ::testing::Values(date(2018, 1, 1), date(2018, 1, 26), date(2018, 3, 30),
                      date(2018, 4, 2), date(2018, 4, 25), date(2018, 6, 11),
                      date(2018, 8, 6), date(2018, 10, 1), date(2018, 12, 25),
                      date(2018, 12, 26), date(2019, 1, 1), date(2019, 1, 28),
                      date(2019, 4, 19), date(2019, 4, 22), date(2019, 4, 25),
                      date(2019, 6, 10), date(2019, 8, 5), date(2019, 10, 7),
                      date(2019, 12, 25), date(2019, 12, 26), date(2020, 1, 1),
                      date(2021, 12, 27), date(2021, 12, 28)));
