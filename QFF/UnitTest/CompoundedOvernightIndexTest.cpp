#include <Actual365.h>
#include <BaseCalendar.h>
#include <CompoundedOvernightIndex.h>
#include <FlatZeroCurve.h>
#include <MarketData.h>
#include <Unadjusted.h>
#include <memory>
#include <string>
#include "gtest/gtest.h"

using namespace qff;

class CompoundedOvernightIndexFixture : public testing::Test {
 public:
  CompoundedOvernightIndexFixture() {
    auto curve =
        std::make_unique<FlatZeroCurve>(date(2019, 1, 2), 0.02, Actual365());
    map<std::string, std::unique_ptr<IInterestRateCurve>> curve_set;
    curve_set.emplace(std::make_pair("OIS", std::move(curve)));
    map<std::string, map<date, double>> past_fixing;
    past_fixing.emplace(std::make_pair(
        "OIS", map<date, double>{std::make_pair(date(2018, 12, 31), 0.026),
                                 std::make_pair(date(2019, 1, 1), 0.025),
                                 std::make_pair(date(2019, 1, 2), 0.024)}));

    market_ = std::make_unique<MarketData>(
        date(2019, 1, 2), std::move(curve_set), std::move(past_fixing));
  }

 protected:
  unique_ptr<MarketData> market_;
};

TEST_F(CompoundedOvernightIndexFixture, GetRate_Past) {
  const CompoundedOvernightIndex index{"USD",
                                       "OIS",
                                       Actual365(),
                                       Period(0, TimeUnit::b),
                                       Period(1, TimeUnit::b),
                                       BaseCalendar(),
                                       Unadjusted()};

  const auto rate = index.GetRate(
      date(2018, 12, 31),
      ShiftDate(date(2018, 12, 31), Period(1, TimeUnit::m), BaseCalendar()),
      *market_);

  EXPECT_NEAR(rate, 0.020372386, 0.0001);
}

TEST_F(CompoundedOvernightIndexFixture, GetRate) {
  const CompoundedOvernightIndex index{"USD",
                                       "OIS",
                                       Actual365(),
                                       Period(0, TimeUnit::b),
                                       Period(1, TimeUnit::b),
                                       BaseCalendar(),
                                       Unadjusted()};

  const auto rate = index.GetRate(
      date(2019, 4, 1),
      ShiftDate(date(2019, 4, 1), Period(3, TimeUnit::m), BaseCalendar()),
      *market_);

  EXPECT_NEAR(rate, 0.020049946, 0.0001);
}

TEST_F(CompoundedOvernightIndexFixture, GetRate_Past_ZeroPublicationLag) {
  const CompoundedOvernightIndex index{"GBP",
                                       "OIS",
                                       Actual365(),
                                       Period(0, TimeUnit::b),
                                       Period(0, TimeUnit::b),
                                       BaseCalendar(),
                                       Unadjusted()};

  const auto rate = index.GetRate(
      date(2018, 12, 31),
      ShiftDate(date(2018, 12, 31), Period(1, TimeUnit::m), BaseCalendar()),
      *market_);

  EXPECT_NEAR(rate, 0.020501616, 0.0001);
}