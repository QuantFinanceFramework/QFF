#include <AustraliaCalendar.h>
#include <vector>
#include "gtest/gtest.h"

using namespace qff;

class AustraliaCalendarTestFixture : public ::testing::TestWithParam<date> {
 protected:
  AustraliaCalendar ausCalendar;
};

TEST_P(AustraliaCalendarTestFixture, isHolidayTest_Holiday) {
  date holiday = GetParam();
  EXPECT_TRUE(ausCalendar.isHoliday(holiday));
}

INSTANTIATE_TEST_CASE_P(
    Holiday, AustraliaCalendarTestFixture,
    ::testing::Values(date(2018, 1, 1), date(2018, 1, 26), date(2018, 3, 30),
                      date(2018, 3, 31), date(2018, 4, 2), date(2018, 4, 25),
                      date(2018, 6, 11), date(2018, 8, 6), date(2018, 10, 1),
                      date(2018, 12, 25), date(2018, 12, 26), date(2019, 1, 1),
                      date(2019, 1, 28), date(2019, 4, 19), date(2019, 4, 20),
                      date(2019, 4, 22), date(2019, 4, 25), date(2019, 6, 10),
                      date(2019, 8, 5), date(2019, 10, 7), date(2019, 12, 25),
                      date(2019, 12, 26), date(2020, 1, 1)));
