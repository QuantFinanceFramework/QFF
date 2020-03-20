#include <Actual365.h>
#include <FixedCashflow.h>
#include <FlatZeroRateCurve.h>
#include <PricingEnvironment.h>

#include <memory>
#include <string>

#include "gtest/gtest.h"

using namespace qff_a;
using boost::gregorian::date;
using std::map;
using std::pair;
using std::string;
using std::unique_ptr;

class FixedCashflowTestFixture : public testing::Test {
 public:
  FixedCashflowTestFixture() {
    auto curve = std::make_unique<FlatZeroRateCurve<double>>(
        date(2019, 1, 1), "USD_FF", Actual365(), 0.0);
    map<std::string, std::unique_ptr<IInterestRateCurve<double>>> curve_set;
    curve_set.emplace(std::make_pair("USD_FF", std::move(curve)));
    map<string, unique_ptr<ICreditCurve<double>>> credit_curve_set;
    map<std::string, map<date, double>> past_fixing;

    map<string, double> fx_today_map;

    environment_ = std::make_unique<PricingEnvironment<double>>(
        date(2019, 1, 1), std::move(curve_set), std::move(past_fixing),
        std::move(credit_curve_set), std::move(fx_today_map));
  }

 protected:
  unique_ptr<PricingEnvironment<double>> environment_;
};

TEST_F(FixedCashflowTestFixture, Evaluate_Expired) {
  FixedCashflow fixed_cashflow(1000000.0, "USD", date(2018, 1, 1), "USD_FF");
  const auto npv = fixed_cashflow.Evaluate(*environment_, "USD");

  EXPECT_NEAR(npv.amount, 0.0, 0.0001);
}

TEST_F(FixedCashflowTestFixture, Evaluate) {
  FixedCashflow fixed_cashflow(1000000.0, "USD", date(2020, 1, 1), "USD_FF");
  const auto npv = fixed_cashflow.Evaluate(*environment_, "USD");

  EXPECT_NEAR(npv.amount, 1000000.0, 0.0001);
}