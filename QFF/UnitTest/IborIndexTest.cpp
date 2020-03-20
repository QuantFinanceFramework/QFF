#include <Actual365.h>
#include <BaseCalendar.h>
#include <FlatZeroRateCurve.h>
#include <IborIndex.h>
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

class IborIndexTestFixture : public testing::Test {
 public:
  IborIndexTestFixture() {
    auto curve = std::make_unique<FlatZeroRateCurve<double>>(
        date(2019, 1, 1), "USD_LIBOR_3M", Actual365(), 0.02);
    map<std::string, std::unique_ptr<IInterestRateCurve<double>>> curve_set;
    curve_set.emplace(std::make_pair("USD_LIBOR_3M", std::move(curve)));
    map<string, unique_ptr<ICreditCurve<double>>> credit_curve_set;
    map<std::string, map<date, double>> past_fixing;
    past_fixing.emplace(std::make_pair(
        "USD_LIBOR_3M",
        map<date, double>{std::make_pair(date(2018, 12, 31), 0.026),
                          std::make_pair(date(2019, 1, 1), 0.025)}));

    map<string, double> fx_today_map;

    environment_ = std::make_unique<PricingEnvironment<double>>(
        date(2019, 1, 1), std::move(curve_set), std::move(past_fixing),
        std::move(credit_curve_set), std::move(fx_today_map));
  }

 protected:
  unique_ptr<PricingEnvironment<double>> environment_;
};

TEST_F(IborIndexTestFixture, GetRate_Past) {
  const IborIndex index{"USD",
                        "USD_LIBOR_3M",
                        Actual365(),
                        Period{-2, TimeUnit::b},
                        BaseCalendar(),
                        Unadjusted(),
                        Period{3, TimeUnit::m}};

  const auto rate =
      index.GetRate(date(2019, 1, 2), date(2019, 4, 2), *environment_);

  EXPECT_NEAR(rate, 0.026, 0.0001);
}

TEST_F(IborIndexTestFixture, GetRate) {
  const IborIndex index{"USD",
                        "USD_LIBOR_3M",
                        Actual365(),
                        Period{-2, TimeUnit::b},
                        BaseCalendar(),
                        Unadjusted(),
                        Period{3, TimeUnit::m}};

  const auto rate =
      index.GetRate(date(2019, 4, 1), date(2019, 7, 1), *environment_);

  EXPECT_NEAR(rate, 0.020049946, 0.0001);
}