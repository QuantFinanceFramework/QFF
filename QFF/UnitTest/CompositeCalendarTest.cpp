#include <CompositeCalendar.h>
#include <LondonCalendar.h>
#include <NewYorkFedCalendar.h>
#include "gtest/gtest.h"

using boost::gregorian::date;
using namespace qff_a;

TEST(CompositeCalendarTest, IsBusinessDayTest_MemorialDay) {
	const auto com = CompositeCalendar(NewYorkFedCalendar(), LondonCalendar());
	const date memorial_day(2019, 5, 27);
  EXPECT_FALSE(com.IsBusinessDay(memorial_day));
}

TEST(CompositeCalendarTest, IsHolidayTest_MemorialDay) {
	const auto com = CompositeCalendar(NewYorkFedCalendar(), LondonCalendar());
	const date memorial_day(2019, 5, 27);
  EXPECT_TRUE(com.IsHoliday(memorial_day));
}

TEST(CompositeCalendarTest, IsBusinessDayTest_QueensBirthday) {
	const auto com = CompositeCalendar(NewYorkFedCalendar(), LondonCalendar());
	const date queens_birthday(2019, 6, 10);
  EXPECT_TRUE(com.IsBusinessDay(queens_birthday));
}

TEST(CompositeCalendarTest, IsHolidayTest_QueensBirthday) {
	const auto com = CompositeCalendar(NewYorkFedCalendar(), LondonCalendar());
	const date queens_birthday(2019, 6, 10);
  EXPECT_FALSE(com.IsHoliday(queens_birthday));
}