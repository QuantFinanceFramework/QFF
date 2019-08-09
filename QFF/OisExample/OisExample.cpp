#include <Actual360.h>
#include <Actual365.h>
#include <CompoundedOvernightIndex.h>
#include <CurveInterpolator.h>
#include <DiscountFactorCurve.h>
#include <FixedCoupon.h>
#include <FloatingCoupon.h>
#include <Interpolation.h>
#include <Leg.h>
#include <MarketData.h>
#include <ModifiedFollowing.h>
#include <NewYorkCalendar.h>
#include <Swap.h>
#include <SwapScheduler.h>
#include <memory>
#include <vector>

using namespace qff;

int main() {
  const date market_date{2019, 3, 19};

  const CurveInterpolator interpolator{LogLinearInterpol, LogLinearExtrapol};
  const Actual365 day_counter{};

  vector ff_pillars{date(2019, 3, 19), date(2019, 3, 20),  date(2019, 4, 1),
                    date(2019, 4, 8),  date(2019, 4, 24),  date(2019, 5, 23),
                    date(2019, 6, 25), date(2019, 7, 24),  date(2019, 8, 23),
                    date(2019, 9, 25), date(2019, 12, 26), date(2020, 3, 25),
                    date(2020, 9, 22), date(2021, 3, 22),  date(2022, 3, 21),
                    date(2023, 3, 21), date(2024, 3, 21),  date(2025, 3, 24),
                    date(2026, 3, 23), date(2027, 3, 22),  date(2028, 3, 21),
                    date(2029, 3, 21), date(2031, 3, 24),  date(2034, 3, 21),
                    date(2039, 3, 21), date(2044, 3, 21),  date(2049, 3, 22),
                    date(2059, 3, 24)};

  vector ff_dfs{1.0,
                0.999933337777482,
                0.99913389744759,
                0.998667454094392,
                0.997602469262895,
                0.995678593702766,
                0.99349732280222,
                0.991600404195084,
                0.989644949297448,
                0.987500445802158,
                0.981620261692297,
                0.976004094586575,
                0.965199821806025,
                0.954982691761777,
                0.935232592449747,
                0.915727875041675,
                0.895789037754247,
                0.875133897409506,
                0.854487069344587,
                0.833462181081861,
                0.812168528439562,
                0.790964066469626,
                0.749057130500852,
                0.690933438810967,
                0.605170011241592,
                0.53257846301933,
                0.469320255300556,
                0.36547586490803};

  auto fed_funds = std::make_unique<DiscountFactorCurve>(
      market_date, std::move(ff_pillars), ff_dfs, interpolator, day_counter);

  map<string, unique_ptr<IInterestRateCurve>> curve_set;
  curve_set.emplace(std::make_pair("USD_FedFunds", std::move(fed_funds)));

  map<string, map<date, double>> past_fixing_set{std::make_pair(
      "USD_FedFunds",
      map<date, double>{std::make_pair(date(2019, 3, 1), 0.024),
                        std::make_pair(date(2019, 3, 2), 0.024),
                        std::make_pair(date(2019, 3, 3), 0.024),
                        std::make_pair(date(2019, 3, 4), 0.024),
                        std::make_pair(date(2019, 3, 5), 0.024),
                        std::make_pair(date(2019, 3, 6), 0.024),
                        std::make_pair(date(2019, 3, 7), 0.024),
                        std::make_pair(date(2019, 3, 8), 0.024),
                        std::make_pair(date(2019, 3, 9), 0.024),
                        std::make_pair(date(2019, 3, 10), 0.024),
                        std::make_pair(date(2019, 3, 11), 0.024),
                        std::make_pair(date(2019, 3, 12), 0.024),
                        std::make_pair(date(2019, 3, 13), 0.024),
                        std::make_pair(date(2019, 3, 14), 0.024),
                        std::make_pair(date(2019, 3, 15), 0.024),
                        std::make_pair(date(2019, 3, 18), 0.024),
                        std::make_pair(date(2019, 3, 19), 0.024)})};

  const MarketData market{market_date, std::move(curve_set),
                          std::move(past_fixing_set)};

  CompoundedOvernightIndex comp_ff{"USD",
                                   "USD_FedFunds",
                                   Actual360(),
                                   Period(0, TimeUnit::b),
                                   Period(1, TimeUnit::b),
                                   NewYorkCalendar(),
                                   ModifiedFollowing(),
                                   Period(0, TimeUnit::b)};

  string discount_curve_name{"USD_FedFunds"};

  auto fixed_cf1 = std::make_unique<FixedCoupon>(
      1000000.0, "USD", date(2019, 3, 4), date(2019, 6, 4), date(2019, 6, 6),
      discount_curve_name, Actual360(), 0.04);
  vector<unique_ptr<ICashflow>> fixed_cf_collection{};
  fixed_cf_collection.emplace_back(std::move(fixed_cf1));
  Leg fixed_leg{std::move(fixed_cf_collection)};

  auto floating_cf1 = std::make_unique<FloatingCoupon>(
      1000000.0, "USD", date(2019, 3, 4), date(2019, 6, 4), date(2019, 6, 6),
      discount_curve_name, Actual360(), comp_ff, 1, 0.0);

  vector<unique_ptr<ICashflow>> floating_cf_collection{};
  floating_cf_collection.emplace_back(std::move(floating_cf1));

  Leg floating_leg{std::move(floating_cf_collection)};

  Swap ois_manual{std::move(fixed_leg), std::move(floating_leg)};

  auto ois_generated = SwapScheduler::MakeInterestRateSwap(
      "USD", 1000000.0, date(2019, 3, 4), date(2019, 6, 4), false,
      "USD_FedFunds", Frequency::Annually, NewYorkCalendar(),
      ModifiedFollowing(), Period(2, TimeUnit::b), Actual360(), 0.04,
      Frequency::Annually, NewYorkCalendar(), ModifiedFollowing(),
      Period(2, TimeUnit::b), Actual360(), comp_ff, 1, 0, true,
      date(2019, 3, 4), 0.0);

  const auto npv = ois_manual.Evaluate(market, "USD");
  std::cout << npv.amount << '\n';

  const auto npv2 = ois_generated->Evaluate(market, "USD");
  std::cout << npv2.amount << '\n';

  return 0;
}