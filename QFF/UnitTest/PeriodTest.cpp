#include <BaseCalendar.h>
#include <Unadjusted.h>
#include <Period.h>
#include "gtest/gtest.h"

using namespace qff;

TEST(ShiftDateTest, TwoBusinessDays) {
  date originalDate(2018, 12, 1);
  EXPECT_EQ(shiftDate(originalDate, {2, TimeUnit::b}, BaseCalendar()),
            date(2018, 12, 4));
}

TEST(ShiftDateTest, MinusTwoBusinessDays) {
  date originalDate(2018, 12, 1);
  EXPECT_EQ(shiftDate(originalDate, {-2, TimeUnit::b}, BaseCalendar()),
            date(2018, 11, 29));
}

TEST(ShiftDateTest, ThreeMonths) {
  date originalDate(2018, 12, 1);
  EXPECT_EQ(
      shiftDate(originalDate, {3, TimeUnit::m}, BaseCalendar(), Unadjusted()),
      date(2019, 3, 1));
}