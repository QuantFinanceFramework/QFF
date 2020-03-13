#include <BaseCalendar.h>
#include <DateFunctions.h>
#include <Unadjusted.h>
#include "gtest/gtest.h"

using namespace qff_a;
using boost::gregorian::date;

TEST(ShiftDateTest, TwoBusinessDays) {
  date original_date(2018, 12, 1);
  EXPECT_EQ(ShiftDate(original_date, {2, TimeUnit::b}, BaseCalendar()),
            date(2018, 12, 4));
}

TEST(ShiftDateTest, MinusTwoBusinessDays) {
  date original_date(2018, 12, 1);
  EXPECT_EQ(ShiftDate(original_date, {-2, TimeUnit::b}, BaseCalendar()),
            date(2018, 11, 29));
}

TEST(ShiftDateTest, ThreeMonths) {
  date original_date(2018, 12, 1);
  EXPECT_EQ(
      ShiftDate(original_date, {3, TimeUnit::m}, BaseCalendar(), Unadjusted()),
      date(2019, 3, 1));
}