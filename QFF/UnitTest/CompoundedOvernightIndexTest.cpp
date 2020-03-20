#include <Actual365.h>
#include <BaseCalendar.h>
#include <CompoundedOvernightIndex.h>
#include <FlatZeroRateCurve.h>
#include <PricingEnvironment.h>
#include <Unadjusted.h>

#include <memory>
#include <string>

#include "gtest/gtest.h"

using namespace qff_a;
using boost::gregorian::date;
using std::map;
using std::string;
using std::unique_ptr;

class CompoundedOvernightIndexTestFixture : public testing::Test {
 public:
  CompoundedOvernightIndexTestFixture() {
    auto curve = std::make_unique<FlatZeroRateCurve<double>>(
        date(2019, 1, 2), "USD_FF", Actual365(), 0.02);
    map<std::string, std::unique_ptr<IInterestRateCurve<double>>> curve_set;
    curve_set.emplace(std::make_pair("USD_FF", std::move(curve)));
    map<string, unique_ptr<ICreditCurve<double>>> credit_curve_set;
    map<std::string, map<date, double>> past_fixing;
    past_fixing.emplace(std::make_pair(
        "USD_FF", map<date, double>{std::make_pair(date(2018, 12, 31), 0.026),
                                    std::make_pair(date(2019, 1, 1), 0.025)}));

    map<string, double> fx_today_map;

    environment_ = std::make_unique<PricingEnvironment<double>>(
        date(2019, 1, 2), std::move(curve_set), std::move(past_fixing),
        std::move(credit_curve_set), std::move(fx_today_map));
  }

 protected:
  unique_ptr<PricingEnvironment<double>> environment_;
};

TEST_F(CompoundedOvernightIndexTestFixture, GetRate_Past) {
  const CompoundedOvernightIndex index{"USD",
                                       "USD_FF",
                                       Actual365(),
                                       Period(0, TimeUnit::b),
                                       Period(1, TimeUnit::b),
                                       BaseCalendar(),
                                       Unadjusted()};

  const auto rate =
      index.GetRate(date(2018, 12, 31), date(2019, 1, 31), *environment_);

  EXPECT_NEAR(rate, 0.020372386, 0.0001);
}

TEST_F(CompoundedOvernightIndexTestFixture, GetRate) {
  const CompoundedOvernightIndex index{"USD",
                                       "USD_FF",
                                       Actual365(),
                                       Period(0, TimeUnit::b),
                                       Period(1, TimeUnit::b),
                                       BaseCalendar(),
                                       Unadjusted()};

  const auto rate =
      index.GetRate(date(2019, 4, 1), date(2019, 7, 1), *environment_);

  EXPECT_NEAR(rate, 0.020049946, 0.0001);
}
