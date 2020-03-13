#include <Target2Calendar.h>

#include "gtest/gtest.h"

using namespace qff_a;
using boost::gregorian::date;

class Target2CalendarTestFixture : public ::testing::TestWithParam<date> {
 protected:
  Target2Calendar target_;
};

TEST_P(Target2CalendarTestFixture, IsHolidayTest_Holidays) {
  const auto holiday = GetParam();
  EXPECT_TRUE(target_.IsHoliday(holiday));
}

INSTANTIATE_TEST_CASE_P(
    Holidays, Target2CalendarTestFixture,
    ::testing::Values(date(2020, 1, 1), date(2020, 4, 10), date(2020, 4, 13),
                      date(2020, 5, 1), date(2020, 12, 25), date(2020, 12, 26),
                      date(2021, 1, 1), date(2021, 4, 2), date(2021, 4, 5),
                      date(2021, 5, 1), date(2021, 12, 25), date(2021, 12, 26),
                      date(2022, 1, 1), date(2022, 4, 15), date(2022, 4, 18),
                      date(2022, 5, 1), date(2022, 12, 25), date(2022, 12, 26),
                      date(2023, 1, 1), date(2023, 4, 7), date(2023, 4, 10),
                      date(2023, 5, 1), date(2023, 12, 25), date(2023, 12, 26),
                      date(2024, 1, 1), date(2024, 3, 29), date(2024, 4, 1),
                      date(2024, 5, 1), date(2024, 12, 25), date(2024, 12, 26),
                      date(2025, 1, 1)));