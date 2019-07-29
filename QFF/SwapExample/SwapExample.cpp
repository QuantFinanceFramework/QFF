#include <Actual360.h>
#include <Actual365.h>
#include <CurveInterpolator.h>
#include <DiscountFactorCurve.h>
#include <FixedCoupon.h>
#include <IborCoupon.h>
#include <IborIndex.h>
#include <Interpolation.h>
#include <Leg.h>
#include <LondonCalendar.h>
#include <MarketData.h>
#include <ModifiedFollowing.h>
#include <NewYorkCalendar.h>
#include <Swap.h>
#include <iostream>
#include <memory>
#include <vector>

using namespace qff;

int main() {
  const date curve_date{2019, 3, 19};
  vector dates{date(2019, 3, 19),  date(2019, 6, 21),  date(2019, 9, 19),
               date(2019, 12, 18), date(2020, 3, 18),  date(2020, 6, 18),
               date(2020, 9, 17),  date(2020, 12, 16), date(2021, 3, 16),
               date(2021, 6, 17),  date(2021, 9, 16),  date(2021, 12, 15),
               date(2022, 3, 15),  date(2022, 6, 16),  date(2023, 3, 21),
               date(2024, 3, 21),  date(2025, 3, 24),  date(2026, 3, 23),
               date(2027, 3, 22),  date(2028, 3, 21),  date(2029, 3, 21),
               date(2031, 3, 24),  date(2034, 3, 21),  date(2039, 3, 21),
               date(2044, 3, 21),  date(2049, 3, 22),  date(2059, 3, 24)};
  vector discount_factors{1.0,
                          0.993172346289134,
                          0.986730317128156,
                          0.980391842332044,
                          0.974001395636903,
                          0.967782724934433,
                          0.961832903220393,
                          0.956118564034139,
                          0.95046465375642,
                          0.944760202885109,
                          0.939229321848812,
                          0.933820408371596,
                          0.92841427525713,
                          0.922845222358382,
                          0.906345084946026,
                          0.884302060331126,
                          0.861608174750851,
                          0.839004876455134,
                          0.816164924750594,
                          0.793202094041263,
                          0.770383945758586,
                          0.725448546172813,
                          0.66360595605489,
                          0.573273128498543,
                          0.497554196810825,
                          0.432445222643056,
                          0.327738486248511};

  const CurveInterpolator interpolator{LogLinearInterpol, LogLinearExtrapol};
  const Actual365 day_counter{};
  auto usd_libor_3m = std::make_unique<DiscountFactorCurve>(
      curve_date, std::move(dates), discount_factors, interpolator,
      day_counter);

  map<string, unique_ptr<IInterestRateCurve>> curve_set;
  curve_set.emplace(std::make_pair("USD_LIBOR_3M", std::move(usd_libor_3m)));

  map<string, map<date, double>> past_fixing_set{std::make_pair(
      "USD_LIBOR_3M",
      map<date, double>{std::make_pair(date(2019, 3, 19), 0.0261275)})};

  const MarketData market{curve_date, std::move(curve_set),
                          std::move(past_fixing_set)};

  IborIndex libor_3m_index{"USD",          "USD_LIBOR_3M",
                           Period{3, TimeUnit::m}, Actual360(),
                           Period{2, TimeUnit::b}, LondonCalendar(),
                           ModifiedFollowing()};

  string discount_curve_name{"USD_FedFunds"};

  auto fixed_cf1 = std::make_unique<FixedCoupon>(
      1000000.0, "USD", date(2019, 3, 21), date(2019, 9, 23), date(2019, 9, 23),
      discount_curve_name, Actual360(), 0.024717703);

  auto fixed_cf2 = std::make_unique<FixedCoupon>(
      1000000.0, "USD", date(2019, 9, 23), date(2020, 3, 23), date(2020, 3, 23),
      discount_curve_name, Actual360(), 0.024717703);

  vector<unique_ptr<ICashflow>> fixed_cf_collection{};
  fixed_cf_collection.emplace_back(std::move(fixed_cf1));
  fixed_cf_collection.emplace_back(std::move(fixed_cf2));

  Leg fixed_leg{std::move(fixed_cf_collection)};

  auto floating_cf1 = std::make_unique<IborCoupon>(
      1000000.0, "USD", date(2019, 3, 21), date(2019, 6, 21), date(2019, 6, 21),
      discount_curve_name, Actual360(), libor_3m_index, 1.0, 0.0);

  auto floating_cf2 = std::make_unique<IborCoupon>(
      1000000.0, string("USD"), date(2019, 6, 21), date(2019, 9, 23),
      date(2019, 9, 23), discount_curve_name, Actual360(), libor_3m_index, 1.0,
      0.0);

  auto floating_cf3 = std::make_unique<IborCoupon>(
      1000000.0, "USD", date(2019, 9, 23), date(2019, 12, 23),
      date(2019, 12, 23), discount_curve_name, Actual360(), libor_3m_index, 1.0,
      0.0);

  auto floating_cf4 = std::make_unique<IborCoupon>(
      1000000.0, "USD", date(2019, 12, 23), date(2020, 3, 23),
      date(2020, 3, 23), discount_curve_name, Actual360(), libor_3m_index, 1.0,
      0.0);

  vector<unique_ptr<ICashflow>> floating_cf_collection{};
  floating_cf_collection.emplace_back(std::move(floating_cf1));
  floating_cf_collection.emplace_back(std::move(floating_cf2));
  floating_cf_collection.emplace_back(std::move(floating_cf3));
  floating_cf_collection.emplace_back(std::move(floating_cf4));

  Leg floating_leg{std::move(floating_cf_collection)};

  Swap libor_3m_irs{std::move(fixed_leg), std::move(floating_leg)};

  auto npv = libor_3m_irs.evaluate(market, "USD");

  std::cout << npv.amount << '/n';
  return 0;
}
