#include <UsBondMarketCalendar.h>

#include "gtest/gtest.h"

using namespace qff_a;
using boost::gregorian::date;

class UsBondMarketCalendarTestFixture : public ::testing::TestWithParam<date> {
 protected:
  UsBondMarketCalendar bond_;
};

TEST_P(UsBondMarketCalendarTestFixture, IsHolidayTest_Holidays) {
  const auto holiday = GetParam();
  EXPECT_TRUE(bond_.IsHoliday(holiday));
}

INSTANTIATE_TEST_CASE_P(
    Holidays, UsBondMarketCalendarTestFixture,
    ::testing::Values(date(2020, 9, 7), date(2020, 10, 12), date(2020, 11, 11),
                      date(2020, 11, 26), date(2020, 12, 25), date(2021, 1, 1),
                      date(2021, 1, 18), date(2021, 2, 15), date(2021, 4, 2),
                      date(2021, 5, 31), date(2021, 7, 5), date(2021, 9, 6),
                      date(2021, 10, 11), date(2021, 11, 11),
                      date(2021, 11, 25), date(2021, 12, 24), date(2022, 1, 1),
                      date(2022, 1, 17), date(2022, 2, 21), date(2022, 4, 15),
                      date(2022, 5, 30), date(2022, 7, 4), date(2022, 9, 5),
                      date(2022, 10, 10), date(2022, 11, 11),
                      date(2022, 11, 24), date(2022, 12, 26), date(2023, 1, 2),
                      date(2023, 1, 16), date(2023, 2, 20), date(2023, 4, 7),
                      date(2023, 5, 29), date(2023, 7, 4), date(2023, 9, 4),
                      date(2023, 10, 9), date(2023, 11, 10), date(2023, 11, 23),
                      date(2023, 12, 25), date(2024, 1, 1), date(2024, 1, 15),
                      date(2024, 2, 19), date(2024, 3, 29), date(2024, 5, 27),
                      date(2024, 7, 4), date(2024, 9, 2), date(2024, 10, 14),
                      date(2024, 11, 11), date(2024, 11, 28),
                      date(2024, 12, 25), date(2025, 1, 1)));
