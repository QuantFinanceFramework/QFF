#include <Actual365.h>
#include <BaseCalendar.h>
#include <FlatZeroCurve.h>
#include <IborIndex.h>
#include <MarketData.h>
#include <Unadjusted.h>
#include <memory>
#include <string>
#include "gtest/gtest.h"

using namespace qff;

class IborIndexTestFixture : public testing::Test {
 public:
  IborIndexTestFixture() {
    auto curve =
        std::make_unique<FlatZeroCurve>(date(2019, 1, 1), 0.02, Actual365());
    map<std::string, std::unique_ptr<IInterestRateCurve>> curve_set;
    curve_set.emplace(std::make_pair("LIBOR_3M", std::move(curve)));
    map<std::string, map<date, double>> past_fixing;
    past_fixing.emplace(std::make_pair(
        "LIBOR_3M",
        map<date, double>{std::make_pair(date(2018, 12, 31), 0.026),
                          std::make_pair(date(2019, 1, 1), 0.025)}));

	market_ = std::make_unique<MarketData>(
        date(2019, 1, 1), std::move(curve_set), std::move(past_fixing));
  }

 protected:
  unique_ptr<MarketData> market_;
};

TEST_F(IborIndexTestFixture, GetRate_Past) {
  const IborIndex index{"USD",
                        "LIBOR_3M",
                        Actual365(),
                        Period{-2, TimeUnit::b},
                        BaseCalendar(),
                        Unadjusted(),
                        Period{3, TimeUnit::m}};

  const auto rate = index.GetRate(
      date(2019, 1, 2),
      ShiftDate(date(2019, 1, 2), Period(3, TimeUnit::m), BaseCalendar()),
      *market_);

  EXPECT_NEAR(rate, 0.026, 0.0001);
}

TEST_F(IborIndexTestFixture, GetRate) {
  const IborIndex index{"USD",
                        "LIBOR_3M",
                        Actual365(),
                        Period{-2, TimeUnit::b},
                        BaseCalendar(),
                        Unadjusted(),
                        Period{3, TimeUnit::m}};

  const auto rate = index.GetRate(
      date(2019, 4, 1),
      ShiftDate(date(2019, 4, 1), Period(3, TimeUnit::m), BaseCalendar()),
      *market_);

  EXPECT_NEAR(rate, 0.020049946, 0.0001);
}