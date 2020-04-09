#include <ImmDates.h>

#include "gtest/gtest.h"

using namespace qff_a;
using boost::gregorian::date;
TEST(NextImmDateTest, FirstImm) {
  date original_date(2020, 12, 18);
  EXPECT_EQ(NextImmDate(original_date), date(2021, 3, 17));
}

TEST(NextImmDateTest, SecondImm) {
  date original_date(2021, 3, 17);
  EXPECT_EQ(NextImmDate(original_date), date(2021, 6, 16));
}

TEST(NextImmDateTest, ThirdImm) {
  date original_date(2022, 9, 17);
  EXPECT_EQ(NextImmDate(original_date), date(2022, 9, 21));
}

TEST(NextImmDateTest, FourthImm) {
  date original_date(2020, 10, 18);
  EXPECT_EQ(NextImmDate(original_date), date(2020, 12, 16));
}