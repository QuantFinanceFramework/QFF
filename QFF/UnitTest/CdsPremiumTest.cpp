#include <Actual365.h>
#include <Actual360.h>
#include <CdsPremium.h>
#include <FlatHazardRateCurve.h>
#include <FlatZeroCurve.h>
#include <MarketData.h>
#include <memory>
#include <string>
#include "gtest/gtest.h"

using namespace qff;
using boost::gregorian::date;
using std::map;
using std::string;
using std::unique_ptr;

class CdsPremiumTestFixture : public testing::Test {
 public:
  CdsPremiumTestFixture() {
    auto ois =
        std::make_unique<FlatZeroCurve>(date(2019, 1, 2), 0.02, Actual365());

    auto credit_curve = std::make_unique<FlatHazardRateCurve>(
        date(2019, 1, 2), 0.02, Actual365());

    map<std::string, std::unique_ptr<IInterestRateCurve>> curve_set;
    curve_set.emplace(std::make_pair("OIS", std::move(ois)));

    map<string, unique_ptr<ICreditCurve>> credit_curve_set;
    credit_curve_set.emplace(std::make_pair("JPM", std::move(credit_curve)));

    map<std::string, map<date, double>> past_fixing;

    market_ = std::make_unique<MarketData>(
        date(2019, 1, 2), std::move(curve_set), std::move(credit_curve_set),
        std::move(past_fixing));
  }

 protected:
  unique_ptr<MarketData> market_;
};

TEST_F(CdsPremiumTestFixture, Evaluate) {
  const CdsPremium premium{1000000.0,
                           "USD",
                           date{2019, 3, 20},
                           date{2019, 6, 20},
                           date{2019, 6, 20},
                           "OIS",
                           "JPM",
                           Actual360(),
                           0.002};
  const auto actual = premium.Evaluate(*market_, "USD");
  EXPECT_NEAR(actual.amount, 503.000005844275, 0.0001);
}