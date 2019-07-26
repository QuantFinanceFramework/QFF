#include <BaseCalendar.h>
#include <Following.h>
#include <ModifiedFollowing.h>
#include <Preceding.h>
#include "gtest/gtest.h"

using namespace qff;

TEST(FollowingTest, AdjustTest) {
  Following convention{};
  date original_date{2017, 12, 31};
  EXPECT_EQ(convention.Adjust(original_date, BaseCalendar()), date(2018, 1, 1));
}

TEST(ModifiedFollowingTest, AdjustTest) {
  ModifiedFollowing convention{};
  date original_date{2017, 12, 31};
  EXPECT_EQ(convention.Adjust(original_date, BaseCalendar()),
            date(2017, 12, 29));
}

TEST(PrecedingTest, AdjustTest) {
  Preceding convention{};
  date original_date{2017, 12, 31};
  EXPECT_EQ(convention.Adjust(original_date, BaseCalendar()),
            date(2017, 12, 29));
}