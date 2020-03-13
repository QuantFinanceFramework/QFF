#include <CompositeCalendar.h>
#include <LondonCalendar.h>
#include <ModifiedFollowing.h>
#include <NewYorkFedCalendar.h>
#include <SwapScheduler.h>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace qff_a;
using boost::gregorian::date;

TEST(SwapSchedulerTest, TestMakeSchedule) {
  const CompositeCalendar calender{NewYorkFedCalendar(), LondonCalendar()};
  const auto schedule = SwapScheduler::MakeSchedule(
	  date(2019, 3, 21), date(2023, 3, 21), Frequency::Quarterly, calender,
	  ModifiedFollowing(), true, date(2019, 3, 21));
  EXPECT_THAT(schedule,
              testing::ElementsAre(
                  date(2019, 3, 21), date(2019, 6, 21), date(2019, 9, 23),
                  date(2019, 12, 23), date(2020, 3, 23), date(2020, 6, 22),
                  date(2020, 9, 21), date(2020, 12, 21), date(2021, 3, 22),
                  date(2021, 6, 21), date(2021, 9, 21), date(2021, 12, 21),
                  date(2022, 3, 21), date(2022, 6, 21), date(2022, 9, 21),
                  date(2022, 12, 21), date(2023, 3, 21)));
}