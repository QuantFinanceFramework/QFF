#include <BaseCalendar.h>
#include <Following.h>
#include <ModifiedFollowing.h>
#include <Preceding.h>
#include "gtest/gtest.h"

using namespace qff;

TEST(FollowingTest, adjustTest) {
  Following convention{};
  date originalDate{2017, 12, 31};
  EXPECT_EQ(convention.adjust(originalDate, BaseCalendar()), date(2018, 1, 1));
}

TEST(ModifiedFollowingTest, adjustTest) {
  ModifiedFollowing convention{};
  date originalDate{2017, 12, 31};
  EXPECT_EQ(convention.adjust(originalDate, BaseCalendar()),
            date(2017, 12, 29));
}

TEST(PrecedingTest, adjustTest) {
  Preceding convention{};
  date originalDate{2017, 12, 31};
  EXPECT_EQ(convention.adjust(originalDate, BaseCalendar()),
            date(2017, 12, 29));
}