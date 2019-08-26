#include <Actual365.h>
#include <AveragedOvernightIndex.h>
#include <BaseCalendar.h>
#include <FlatZeroCurve.h>
#include <MarketData.h>
#include <Unadjusted.h>
#include <memory>
#include <string>
#include "gtest/gtest.h"

using namespace qff;
using boost::gregorian::date;
using std::map;
using std::string;
using std::unique_ptr;

class AveragedOvernightIndexTestFixture : public testing::Test {
 public:
  AveragedOvernightIndexTestFixture() {
    auto curve =
        std::make_unique<FlatZeroCurve>(date(2019, 1, 2), 0.02, Actual365());
    map<std::string, std::unique_ptr<IInterestRateCurve>> curve_set;
    curve_set.emplace(std::make_pair("OIS", std::move(curve)));
    map<string, unique_ptr<ICreditCurve>> credit_curve_set;
    map<std::string, map<date, double>> past_fixing;
    past_fixing.emplace(std::make_pair(
        "OIS", map<date, double>{std::make_pair(date(2018, 12, 31), 0.026),
                                 std::make_pair(date(2019, 1, 1), 0.025),
                                 std::make_pair(date(2019, 1, 2), 0.024)}));

    market_ = std::make_unique<MarketData>(
        date(2019, 1, 2), std::move(curve_set), std::move(credit_curve_set),
        std::move(past_fixing));
  }

 protected:
  unique_ptr<MarketData> market_;
};

TEST_F(AveragedOvernightIndexTestFixture, GetRate_Past) {
  const AveragedOvernightIndex index{"USD",
                                     "OIS",
                                     Actual365(),
                                     Period(0, TimeUnit::b),
                                     Period(1, TimeUnit::b),
                                     BaseCalendar(),
                                     Unadjusted(),
                                     Period(-2, TimeUnit::b),
                                     false};

  const auto rate =
      index.GetRate(date(2018, 12, 31), date(2019, 1, 31), *market_);

  EXPECT_NEAR(rate, 0.02035577555959, 0.0001);
}

TEST_F(AveragedOvernightIndexTestFixture, GetRate) {
  const AveragedOvernightIndex index{"USD",
                                     "OIS",
                                     Actual365(),
                                     Period(0, TimeUnit::b),
                                     Period(1, TimeUnit::b),
                                     BaseCalendar(),
                                     Unadjusted(),
                                     Period(-2, TimeUnit::b),
                                     false};

  const auto rate = index.GetRate(date(2019, 4, 1), date(2019, 5, 1), *market_);

  EXPECT_NEAR(rate, 0.02000098634341, 0.0001);
}
