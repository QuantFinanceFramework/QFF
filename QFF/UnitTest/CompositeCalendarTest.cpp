#include <CompositeCalendar.h>
#include <LondonCalendar.h>
#include <NewYorkCalendar.h>
#include "gtest/gtest.h"

using namespace qff;

TEST(CompositeCalendarTest, isBusinessDayTest_MemorialDay) {
  auto com = CompositeCalendar(NewYorkCalendar(), LondonCalendar());
  date memorialDay(2019, 5, 27);
  EXPECT_FALSE(com.isBusinessDay(memorialDay));
}

TEST(CompositeCalendarTest, isHolidayTest_MemorialDay) {
  auto com = CompositeCalendar(NewYorkCalendar(), LondonCalendar());
  date memorialDay(2019, 5, 27);
  EXPECT_TRUE(com.isHoliday(memorialDay));
}

TEST(CompositeCalendarTest, isBusinessDayTest_QueensBirthday) {
  auto com = CompositeCalendar(NewYorkCalendar(), LondonCalendar());
  date queensBirthday(2019, 6, 10);
  EXPECT_TRUE(com.isBusinessDay(queensBirthday));
}

TEST(CompositeCalendarTest, isHolidayTest_QueensBirthday) {
  auto com = CompositeCalendar(NewYorkCalendar(), LondonCalendar());
  date queensBirthday(2019, 6, 10);
  EXPECT_FALSE(com.isHoliday(queensBirthday));
}