#include <Actual360.h>
#include <Actual365.h>
#include <CompoundedOvernightCoupon.h>
#include <CurveInterpolator.h>
#include <DiscountFactorCurve.h>
#include <FixedCoupon.h>
#include <Interpolation.h>
#include <Leg.h>
#include <MarketData.h>
#include <ModifiedFollowing.h>
#include <NewYorkCalendar.h>
#include <OvernightIndex.h>
#include <Swap.h>
#include <SwapScheduler.h>
#include <memory>
#include <numeric>
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
      map<date, double>{std::make_pair(date(2019, 3, 19), 0.0263263)})};

  const MarketData market{market_date, std::move(curve_set),
                          std::move(past_fixing_set)};

  OvernightIndex ff_index{"USD",
                          "USD_FedFunds",
                          Period{1, TimeUnit::b},
                          Actual360(),
                          Period{0, TimeUnit::b},
                          Period{1, TimeUnit::b},
                          NewYorkCalendar(),
                          ModifiedFollowing()};

  string discount_curve_name{"USD_FedFunds"};

  auto fixed_cf1 = std::make_unique<FixedCoupon>(
      1000000.0, "USD", date(2019, 3, 21), date(2019, 6, 21), date(2019, 6, 25),
      discount_curve_name, Actual360(), 0.04);
  vector<unique_ptr<ICashflow>> fixed_cf_collection{};
  fixed_cf_collection.emplace_back(std::move(fixed_cf1));
  Leg fixed_leg{std::move(fixed_cf_collection)};

  vector accruals{date(2019, 3, 21), date(2019, 3, 22), date(2019, 3, 25),
                  date(2019, 3, 26), date(2019, 3, 27), date(2019, 3, 28),
                  date(2019, 3, 29), date(2019, 4, 1),  date(2019, 4, 2),
                  date(2019, 4, 3),  date(2019, 4, 4),  date(2019, 4, 5),
                  date(2019, 4, 8),  date(2019, 4, 9),  date(2019, 4, 10),
                  date(2019, 4, 11), date(2019, 4, 12), date(2019, 4, 15),
                  date(2019, 4, 16), date(2019, 4, 17), date(2019, 4, 18),
                  date(2019, 4, 19), date(2019, 4, 22), date(2019, 4, 23),
                  date(2019, 4, 24), date(2019, 4, 25), date(2019, 4, 26),
                  date(2019, 4, 29), date(2019, 4, 30), date(2019, 5, 1),
                  date(2019, 5, 2),  date(2019, 5, 3),  date(2019, 5, 6),
                  date(2019, 5, 7),  date(2019, 5, 8),  date(2019, 5, 9),
                  date(2019, 5, 10), date(2019, 5, 13), date(2019, 5, 14),
                  date(2019, 5, 15), date(2019, 5, 16), date(2019, 5, 17),
                  date(2019, 5, 20), date(2019, 5, 21), date(2019, 5, 22),
                  date(2019, 5, 23), date(2019, 5, 24), date(2019, 5, 28),
                  date(2019, 5, 29), date(2019, 5, 30), date(2019, 5, 31),
                  date(2019, 6, 3),  date(2019, 6, 4),  date(2019, 6, 5),
                  date(2019, 6, 6),  date(2019, 6, 7),  date(2019, 6, 10),
                  date(2019, 6, 11), date(2019, 6, 12), date(2019, 6, 13),
                  date(2019, 6, 14), date(2019, 6, 17), date(2019, 6, 18),
                  date(2019, 6, 19), date(2019, 6, 20), date(2019, 6, 21),
                  date(2019, 6, 24)};

  auto floating_cf1 = std::make_unique<CompoundedOvernightCoupon>(
      1000000.0, "USD", accruals, date(2019, 6, 25), discount_curve_name,
      Actual360(), ff_index, 1.0, 0.0, Period{0, TimeUnit::b});

  vector<unique_ptr<ICashflow>> floating_cf_collection{};
  floating_cf_collection.emplace_back(std::move(floating_cf1));

  Leg floating_leg{std::move(floating_cf_collection)};

  Swap ois_manual{std::move(fixed_leg), std::move(floating_leg)};
  const auto npv = ois_manual.Evaluate(market, "USD");
  std::cout << npv.amount << '\n';
  return 0;
}