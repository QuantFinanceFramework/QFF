#include <BaseCalendar.h>
#include <Following.h>
#include <ModifiedFollowing.h>
#include <Preceding.h>
#include "gtest/gtest.h"

using boost::gregorian::date;
using namespace qff_a;

TEST(FollowingTest, Adjust) {
  Following convention{};
  date original_date{2017, 12, 31};
  EXPECT_EQ(convention.Adjust(original_date, BaseCalendar()), date(2018, 1, 1));
}

TEST(ModifiedFollowingTest, Adjust) {
  ModifiedFollowing convention{};
  date original_date{2017, 12, 31};
  EXPECT_EQ(convention.Adjust(original_date, BaseCalendar()),
            date(2017, 12, 29));
}

TEST(PrecedingTest, Adjust) {
  Preceding convention{};
  date original_date{2017, 12, 31};
  EXPECT_EQ(convention.Adjust(original_date, BaseCalendar()),
            date(2017, 12, 29));
}