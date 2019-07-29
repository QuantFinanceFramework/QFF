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
#include <Swap.h>
#include <Thirty360Isda.h>
#include <iostream>
#include <memory>
#include <vector>

using namespace qff;

int main() {
  const date market_date{2019, 3, 19};

  vector libor_3m_pillars{
      date(2019, 3, 19),  date(2019, 6, 21),  date(2019, 9, 19),
      date(2019, 12, 18), date(2020, 3, 18),  date(2020, 6, 18),
      date(2020, 9, 17),  date(2020, 12, 16), date(2021, 3, 16),
      date(2021, 6, 17),  date(2021, 9, 16),  date(2021, 12, 15),
      date(2022, 3, 15),  date(2022, 6, 16),  date(2023, 3, 21),
      date(2024, 3, 21),  date(2025, 3, 24),  date(2026, 3, 23),
      date(2027, 3, 22),  date(2028, 3, 21),  date(2029, 3, 21),
      date(2031, 3, 24),  date(2034, 3, 21),  date(2039, 3, 21),
      date(2044, 3, 21),  date(2049, 3, 22),  date(2059, 3, 24)};

  vector libor_3m_dfs{1.0,
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
      market_date, std::move(libor_3m_pillars), libor_3m_dfs, interpolator,
      day_counter);

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
  curve_set.emplace(std::make_pair("USD_LIBOR_3M", std::move(usd_libor_3m)));
  curve_set.emplace(std::make_pair("USD_FedFunds", std::move(fed_funds)));

  map<string, map<date, double>> past_fixing_set{std::make_pair(
      "USD_LIBOR_3M",
      map<date, double>{std::make_pair(date(2019, 3, 19), 0.0263263)})};

  const MarketData market{market_date, std::move(curve_set),
                          std::move(past_fixing_set)};

  IborIndex libor_3m_index{"USD",
                           "USD_LIBOR_3M",
                           Period{3, TimeUnit::m},
                           Actual360(),
                           Period{-2, TimeUnit::b},
                           LondonCalendar(),
                           ModifiedFollowing()};

  string discount_curve_name{"USD_FedFunds"};

  auto fixed_cf1 = std::make_unique<FixedCoupon>(
      1000000.0, "USD", date(2019, 3, 21), date(2019, 9, 23), date(2019, 9, 23),
      discount_curve_name, Thirty360Isda(), 0.024717703);

  auto fixed_cf2 = std::make_unique<FixedCoupon>(
      1000000.0, "USD", date(2019, 9, 23), date(2020, 3, 23), date(2020, 3, 23),
      discount_curve_name, Thirty360Isda(), 0.024717703);

  auto fixed_cf3 = std::make_unique<FixedCoupon>(
      1000000.0, "USD", date(2020, 3, 23), date(2020, 9, 21), date(2020, 9, 21),
      discount_curve_name, Thirty360Isda(), 0.024717703);

  auto fixed_cf4 = std::make_unique<FixedCoupon>(
      1000000.0, "USD", date(2020, 9, 21), date(2021, 3, 22), date(2021, 3, 22),
      discount_curve_name, Thirty360Isda(), 0.024717703);

  auto fixed_cf5 = std::make_unique<FixedCoupon>(
      1000000.0, "USD", date(2021, 3, 22), date(2021, 9, 21), date(2021, 9, 21),
      discount_curve_name, Thirty360Isda(), 0.024717703);

  auto fixed_cf6 = std::make_unique<FixedCoupon>(
      1000000.0, "USD", date(2021, 9, 21), date(2022, 3, 21), date(2022, 3, 21),
      discount_curve_name, Thirty360Isda(), 0.024717703);

  auto fixed_cf7 = std::make_unique<FixedCoupon>(
      1000000.0, "USD", date(2022, 3, 21), date(2022, 9, 21), date(2022, 9, 21),
      discount_curve_name, Thirty360Isda(), 0.024717703);

  auto fixed_cf8 = std::make_unique<FixedCoupon>(
      1000000.0, "USD", date(2022, 9, 21), date(2023, 3, 21), date(2023, 3, 21),
      discount_curve_name, Thirty360Isda(), 0.024717703);

  vector<unique_ptr<ICashflow>> fixed_cf_collection{};
  fixed_cf_collection.emplace_back(std::move(fixed_cf1));
  fixed_cf_collection.emplace_back(std::move(fixed_cf2));
  fixed_cf_collection.emplace_back(std::move(fixed_cf3));
  fixed_cf_collection.emplace_back(std::move(fixed_cf4));
  fixed_cf_collection.emplace_back(std::move(fixed_cf5));
  fixed_cf_collection.emplace_back(std::move(fixed_cf6));
  fixed_cf_collection.emplace_back(std::move(fixed_cf7));
  fixed_cf_collection.emplace_back(std::move(fixed_cf8));

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

  auto floating_cf5 = std::make_unique<IborCoupon>(
      1000000.0, "USD", date(2020, 3, 23), date(2020, 6, 22), date(2020, 6, 22),
      discount_curve_name, Actual360(), libor_3m_index, 1.0, 0.0);

  auto floating_cf6 = std::make_unique<IborCoupon>(
      1000000.0, string("USD"), date(2020, 6, 22), date(2020, 9, 21),
      date(2020, 9, 21), discount_curve_name, Actual360(), libor_3m_index, 1.0,
      0.0);

  auto floating_cf7 = std::make_unique<IborCoupon>(
      1000000.0, "USD", date(2020, 9, 21), date(2020, 12, 21),
      date(2020, 12, 21), discount_curve_name, Actual360(), libor_3m_index, 1.0,
      0.0);

  auto floating_cf8 = std::make_unique<IborCoupon>(
      1000000.0, "USD", date(2020, 12, 21), date(2021, 3, 22),
      date(2021, 3, 22), discount_curve_name, Actual360(), libor_3m_index, 1.0,
      0.0);

	  auto floating_cf9 = std::make_unique<IborCoupon>(
      1000000.0, "USD", date(2021, 3, 22), date(2021, 6, 21), date(2021, 6, 21),
      discount_curve_name, Actual360(), libor_3m_index, 1.0, 0.0);

  auto floating_cf10 = std::make_unique<IborCoupon>(
      1000000.0, string("USD"), date(2021, 6, 21), date(2021, 9, 21),
      date(2021, 9, 21), discount_curve_name, Actual360(), libor_3m_index, 1.0,
      0.0);

  auto floating_cf11 = std::make_unique<IborCoupon>(
      1000000.0, "USD", date(2021, 9, 21), date(2021, 12, 21),
      date(2021, 12, 21), discount_curve_name, Actual360(), libor_3m_index, 1.0,
      0.0);

  auto floating_cf12 = std::make_unique<IborCoupon>(
      1000000.0, "USD", date(2021, 12, 21), date(2022, 3, 21),
      date(2022, 3, 21), discount_curve_name, Actual360(), libor_3m_index, 1.0,
      0.0);

  auto floating_cf13 = std::make_unique<IborCoupon>(
      1000000.0, "USD", date(2022, 3, 21), date(2022, 6, 21), date(2022, 6, 21),
      discount_curve_name, Actual360(), libor_3m_index, 1.0, 0.0);

  auto floating_cf14 = std::make_unique<IborCoupon>(
      1000000.0, string("USD"), date(2022, 6, 21), date(2022, 9, 21),
      date(2022, 9, 21), discount_curve_name, Actual360(), libor_3m_index, 1.0,
      0.0);

  auto floating_cf15 = std::make_unique<IborCoupon>(
      1000000.0, "USD", date(2022, 9, 21), date(2022, 12, 21),
      date(2022, 12, 21), discount_curve_name, Actual360(), libor_3m_index, 1.0,
      0.0);

  auto floating_cf16 = std::make_unique<IborCoupon>(
      1000000.0, "USD", date(2022, 12, 21), date(2023, 3, 21),
      date(2023, 3, 21), discount_curve_name, Actual360(), libor_3m_index, 1.0,
      0.0);

  vector<unique_ptr<ICashflow>> floating_cf_collection{};
  floating_cf_collection.emplace_back(std::move(floating_cf1));
  floating_cf_collection.emplace_back(std::move(floating_cf2));
  floating_cf_collection.emplace_back(std::move(floating_cf3));
  floating_cf_collection.emplace_back(std::move(floating_cf4));
  floating_cf_collection.emplace_back(std::move(floating_cf5));
  floating_cf_collection.emplace_back(std::move(floating_cf6));
  floating_cf_collection.emplace_back(std::move(floating_cf7));
  floating_cf_collection.emplace_back(std::move(floating_cf8));
  floating_cf_collection.emplace_back(std::move(floating_cf9));
  floating_cf_collection.emplace_back(std::move(floating_cf10));
  floating_cf_collection.emplace_back(std::move(floating_cf11));
  floating_cf_collection.emplace_back(std::move(floating_cf12));
  floating_cf_collection.emplace_back(std::move(floating_cf13));
  floating_cf_collection.emplace_back(std::move(floating_cf14));
  floating_cf_collection.emplace_back(std::move(floating_cf15));
  floating_cf_collection.emplace_back(std::move(floating_cf16));

  Leg floating_leg{std::move(floating_cf_collection)};

  Swap libor_3m_irs{std::move(fixed_leg), std::move(floating_leg)};

  auto npv = libor_3m_irs.Evaluate(market, "USD");

  std::cout << npv.amount << '/n';
  return 0;
}
