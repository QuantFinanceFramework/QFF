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

TEST(CurrencyTest, Add) {
  const Currency a{"USD", 100.0};
  const Currency b{"USD", 200.0};
  const auto c = a + b;
  EXPECT_NEAR(c.amount, 300.0, 0.0001);
}

TEST(CurrencyTest, Minus) {
  const Currency a{"USD", 100.0};
  const Currency b{"USD", 200.0};
  const auto c = a - b;
  EXPECT_NEAR(c.amount, -100.0, 0.0001);
}

TEST(CurrencyTest, Add_Different_Currencies) {
  const Currency a{"USD", 100.0};
  const Currency b{"EUR", 100.0};
  EXPECT_ANY_THROW(a + b);
}

class CurrencyTestFixture : public testing::Test {
 public:
  CurrencyTestFixture() {
    auto curve = std::make_unique<FlatZeroRateCurve<double>>(
        date(2019, 1, 1), "USD_FF", Actual365(), 0.0);
    map<std::string, std::unique_ptr<IInterestRateCurve<double>>> curve_set;
    curve_set.emplace(std::make_pair("USD_FF", std::move(curve)));
    map<string, unique_ptr<ICreditCurve<double>>> credit_curve_set;
    map<std::string, map<date, double>> past_fixing;

    map<string, double> fx_today_map;
    fx_today_map.emplace(pair(string("EURUSD"), 1.1));
    fx_today_map.emplace(pair(string("USDJPY"), 110.0));

    environment_ = std::make_unique<PricingEnvironment<double>>(
        date(2019, 1, 1), std::move(curve_set), std::move(past_fixing),
        std::move(credit_curve_set), std::move(fx_today_map));
    fixed_cashflow_ = std::make_unique<FixedCashflow>(
        1000000.0, "USD", date(2020, 1, 1), "USD_FF");
  }

 protected:
  unique_ptr<PricingEnvironment<double>> environment_;
  unique_ptr<FixedCashflow> fixed_cashflow_;
};

TEST_F(CurrencyTestFixture, Evaluate_No_Convertion) {
  const auto npv = fixed_cashflow_->Evaluate(*environment_, "USD");

  EXPECT_NEAR(npv.amount, 1000000.0, 0.0001);
}

TEST_F(CurrencyTestFixture, Evaluate_Convertion) {
  const auto npv = fixed_cashflow_->Evaluate(*environment_, "JPY");

  EXPECT_NEAR(npv.amount, 110000000.0, 0.0001);
}

TEST_F(CurrencyTestFixture, Evaluate_Inversion) {
  const auto npv = fixed_cashflow_->Evaluate(*environment_, "EUR");

  EXPECT_NEAR(npv.amount, 909090.9091, 0.0001);
}

