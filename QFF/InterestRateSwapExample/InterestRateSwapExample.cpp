#include <Actual360.h>
#include <Actual365.h>
#include <AveragedOvernightIndex.h>
#include <CompositeCalendar.h>
#include <CompoundedOvernightIndex.h>
#include <CurveInterpolator.h>
#include <DiscountFactorCurve.h>
#include <IborIndex.h>
#include <Interpolation.h>
#include <Leg.h>
#include <LondonCalendar.h>
#include <MarketData.h>
#include <ModifiedFollowing.h>
#include <NewYorkCalendar.h>
#include <Swap.h>
#include <SwapScheduler.h>
#include <Thirty360Isda.h>
#include <memory>
#include <vector>

using namespace qff;

int main() {
  const date market_date{2019, 4, 10};

  const CurveInterpolator interpolator{LogLinearInterpol, LogLinearExtrapol};
  const Actual365 day_counter{};

  vector ff_pillars{date(2019, 4, 10),  date(2019, 4, 11), date(2019, 4, 23),
                    date(2019, 4, 30),  date(2019, 5, 15), date(2019, 6, 14),
                    date(2019, 7, 16),  date(2019, 8, 14), date(2019, 9, 16),
                    date(2019, 10, 17), date(2020, 1, 15), date(2020, 4, 15),
                    date(2020, 10, 13), date(2021, 4, 12), date(2022, 4, 12),
                    date(2023, 4, 12),  date(2024, 4, 12), date(2025, 4, 14),
                    date(2026, 4, 13),  date(2027, 4, 12), date(2028, 4, 12),
                    date(2029, 4, 12),  date(2031, 4, 15), date(2034, 4, 12),
                    date(2039, 4, 12),  date(2044, 4, 12), date(2049, 4, 12),
                    date(2059, 4, 14)};

  vector ff_dfs{1.0,
                0.999933060036814,
                0.999130291045838,
                0.998662818019684,
                0.997662058686208,
                0.995666785372217,
                0.993547188517104,
                0.991670166146898,
                0.989508739055556,
                0.987543379364211,
                0.981897675254078,
                0.976450670204002,
                0.966507784738812,
                0.957061923551266,
                0.93850904682124,
                0.919941928129991,
                0.900866632043426,
                0.88100225718891,
                0.86102483897881,
                0.840725601470964,
                0.820345186093549,
                0.799861038269815,
                0.759285732624141,
                0.702560741801866,
                0.617919636280566,
                0.546496626071902,
                0.484272219004205,
                0.381066661016916};

  vector libor_3m_pillars{
      date(2019, 4, 10),  date(2019, 7, 12),  date(2019, 9, 19),
      date(2019, 12, 18), date(2020, 3, 18),  date(2020, 6, 18),
      date(2020, 9, 17),  date(2020, 12, 16), date(2021, 3, 16),
      date(2021, 6, 17),  date(2021, 9, 16),  date(2021, 12, 15),
      date(2022, 3, 15),  date(2022, 6, 16),  date(2023, 4, 12),
      date(2024, 4, 12),  date(2025, 4, 14),  date(2026, 4, 13),
      date(2027, 4, 12),  date(2028, 4, 12),  date(2029, 4, 12),
      date(2031, 4, 15),  date(2034, 4, 12),  date(2039, 4, 12),
      date(2044, 4, 12),  date(2049, 4, 12),  date(2059, 4, 14)};

  vector libor_3m_dfs{1.0,
                      0.993375470765473,
                      0.988574512099469,
                      0.982431456339511,
                      0.976321420472281,
                      0.970456929836142,
                      0.964902535731033,
                      0.959586573019396,
                      0.954350030543054,
                      0.949047761594921,
                      0.943893793847415,
                      0.938829986054228,
                      0.933764987974085,
                      0.928526156745888,
                      0.911614655482877,
                      0.890657808353375,
                      0.86893249956175,
                      0.84718148983994,
                      0.82518698042637,
                      0.803173244039273,
                      0.78119121095432,
                      0.737852153499424,
                      0.677411309128505,
                      0.588239132082424,
                      0.513513201101991,
                      0.449232212159018,
                      0.344825397474425};

  auto fed_funds = std::make_unique<DiscountFactorCurve>(
      market_date, std::move(ff_pillars), ff_dfs, interpolator, day_counter);

  auto usd_libor_3m = std::make_unique<DiscountFactorCurve>(
      market_date, std::move(libor_3m_pillars), libor_3m_dfs, interpolator,
      day_counter);

  map<string, unique_ptr<IInterestRateCurve>> curve_set;
  curve_set.emplace(std::make_pair("USD_FedFunds", std::move(fed_funds)));
  curve_set.emplace(std::make_pair("USD_LIBOR_3M", std::move(usd_libor_3m)));

  map<string, map<date, double>> past_fixing_set{
      std::make_pair("USD_FedFunds",
                     map{std::make_pair(date(2019, 3, 1), 0.024),
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
                         std::make_pair(date(2019, 3, 16), 0.024),
                         std::make_pair(date(2019, 3, 17), 0.024),
                         std::make_pair(date(2019, 3, 18), 0.024),
                         std::make_pair(date(2019, 3, 19), 0.024),
                         std::make_pair(date(2019, 3, 20), 0.0241),
                         std::make_pair(date(2019, 3, 21), 0.0241),
                         std::make_pair(date(2019, 3, 22), 0.0241),
                         std::make_pair(date(2019, 3, 23), 0.0241),
                         std::make_pair(date(2019, 3, 24), 0.0241),
                         std::make_pair(date(2019, 3, 25), 0.024),
                         std::make_pair(date(2019, 3, 26), 0.024),
                         std::make_pair(date(2019, 3, 27), 0.0241),
                         std::make_pair(date(2019, 3, 28), 0.0241),
                         std::make_pair(date(2019, 3, 29), 0.0243),
                         std::make_pair(date(2019, 3, 30), 0.0243),
                         std::make_pair(date(2019, 3, 31), 0.0243),
                         std::make_pair(date(2019, 4, 1), 0.0241),
                         std::make_pair(date(2019, 4, 2), 0.0241),
                         std::make_pair(date(2019, 4, 3), 0.0241),
                         std::make_pair(date(2019, 4, 4), 0.0241),
                         std::make_pair(date(2019, 4, 5), 0.0241),
                         std::make_pair(date(2019, 4, 6), 0.0241),
                         std::make_pair(date(2019, 4, 7), 0.0241),
                         std::make_pair(date(2019, 4, 8), 0.0241),
                         std::make_pair(date(2019, 4, 9), 0.0241)}),
      std::make_pair("USD_LIBOR_3M",
                     map{std::make_pair(date(2019, 3, 1), 0.025985),
                         std::make_pair(date(2019, 3, 4), 0.0260763),
                         std::make_pair(date(2019, 3, 5), 0.0260663),
                         std::make_pair(date(2019, 3, 6), 0.025945),
                         std::make_pair(date(2019, 3, 7), 0.0260063),
                         std::make_pair(date(2019, 3, 8), 0.0259663),
                         std::make_pair(date(2019, 3, 11), 0.0260825),
                         std::make_pair(date(2019, 3, 12), 0.0259325),
                         std::make_pair(date(2019, 3, 13), 0.0261088),
                         std::make_pair(date(2019, 3, 14), 0.0261463),
                         std::make_pair(date(2019, 3, 15), 0.0262525),
                         std::make_pair(date(2019, 3, 18), 0.0263263),
                         std::make_pair(date(2019, 3, 19), 0.0261275),
                         std::make_pair(date(2019, 3, 20), 0.02607),
                         std::make_pair(date(2019, 3, 21), 0.026015),
                         std::make_pair(date(2019, 3, 22), 0.0260988),
                         std::make_pair(date(2019, 3, 25), 0.0260875),
                         std::make_pair(date(2019, 3, 26), 0.0259738),
                         std::make_pair(date(2019, 3, 27), 0.02601),
                         std::make_pair(date(2019, 3, 28), 0.0259175),
                         std::make_pair(date(2019, 3, 29), 0.0259975),
                         std::make_pair(date(2019, 4, 1), 0.025955),
                         std::make_pair(date(2019, 4, 2), 0.0260238),
                         std::make_pair(date(2019, 4, 3), 0.0259775),
                         std::make_pair(date(2019, 4, 4), 0.0258863),
                         std::make_pair(date(2019, 4, 5), 0.0259213),
                         std::make_pair(date(2019, 4, 8), 0.02584),
                         std::make_pair(date(2019, 4, 9), 0.0258125),
                         std::make_pair(date(2019, 4, 10), 0.026035)})};

  const MarketData market{market_date, std::move(curve_set),
                          std::move(past_fixing_set)};

  CompoundedOvernightIndex comp_ff{"USD",
                                   "USD_FedFunds",
                                   Actual360(),
                                   Period(0, TimeUnit::b),
                                   Period(1, TimeUnit::b),
                                   NewYorkCalendar(),
                                   ModifiedFollowing()};

  AveragedOvernightIndex averaged_ff{"USD",
                                     "USD_FedFunds",
                                     Actual360(),
                                     Period(0, TimeUnit::b),
                                     Period(1, TimeUnit::b),
                                     NewYorkCalendar(),
                                     ModifiedFollowing(),
                                     Period(-2, TimeUnit::b),
                                     false};

  IborIndex libor_3m_index{"USD",
                           "USD_LIBOR_3M",
                           Actual360(),
                           Period{-2, TimeUnit::b},
                           LondonCalendar(),
                           ModifiedFollowing(),
                           Period{3, TimeUnit::m}};

  string discount_curve_name{"USD_FedFunds"};

  auto ois = SwapScheduler::MakeInterestRateSwap(
      "USD", 10000000.0, date(2019, 3, 10), date(2022, 3, 10), false,
      "USD_FedFunds", Frequency::Annually, NewYorkCalendar(),
      ModifiedFollowing(), Period(2, TimeUnit::b), Actual360(), 0.025,
      Frequency::Annually, NewYorkCalendar(), ModifiedFollowing(),
      Period(2, TimeUnit::b), Actual360(), comp_ff, 1, 0, true,
      date(2019, 3, 10), 0.0);

  auto irs = SwapScheduler::MakeInterestRateSwap(
      "USD", 10000000.0, date(2019, 3, 10), date(2022, 3, 10), false,
      discount_curve_name, Frequency::Semiannually,
      CompositeCalendar(NewYorkCalendar(), LondonCalendar()),
      ModifiedFollowing(), Period{0, TimeUnit::b}, Thirty360Isda(), 0.025,
      Frequency::Quarterly,
      CompositeCalendar(NewYorkCalendar(), LondonCalendar()),
      ModifiedFollowing(), Period{0, TimeUnit::b}, Actual360(), libor_3m_index,
      1.0, 0.0, true, date(2019, 3, 10), 0.0);

  auto ois2 = SwapScheduler::MakeInterestRateSwap(
      "USD", 10000000.0, date(2019, 4, 12), date(2022, 4, 12), false,
      "USD_FedFunds", Frequency::Annually, NewYorkCalendar(),
      ModifiedFollowing(), Period(2, TimeUnit::b), Actual360(), 0.025,
      Frequency::Annually, NewYorkCalendar(), ModifiedFollowing(),
      Period(2, TimeUnit::b), Actual360(), comp_ff, 1, 0, true,
      date(2019, 4, 12), 0.0);

  auto irs2 = SwapScheduler::MakeInterestRateSwap(
      "USD", 10000000.0, date(2019, 4, 12), date(2022, 4, 12), false,
      discount_curve_name, Frequency::Semiannually,
      CompositeCalendar(NewYorkCalendar(), LondonCalendar()),
      ModifiedFollowing(), Period{0, TimeUnit::b}, Thirty360Isda(), 0.025,
      Frequency::Quarterly,
      CompositeCalendar(NewYorkCalendar(), LondonCalendar()),
      ModifiedFollowing(), Period{0, TimeUnit::b}, Actual360(), libor_3m_index,
      1.0, 0.0, true, date(2019, 4, 12), 0.0);

  auto ois3 = SwapScheduler::MakeInterestRateSwap(
      "USD", 10000000.0, date(2019, 3, 28), date(2022, 3, 28), false,
      "USD_FedFunds", Frequency::Annually, NewYorkCalendar(),
      ModifiedFollowing(), Period(2, TimeUnit::b), Actual360(), 0.0,
      Frequency::Annually, NewYorkCalendar(), ModifiedFollowing(),
      Period(2, TimeUnit::b), Actual360(), comp_ff, 1, 0, true,
      date(2019, 3, 28), 0.0);

  auto ff_swap = SwapScheduler::MakeBasisSwap(
      "USD", 10000000.0, date(2019, 4, 12), date(2022, 4, 12), "USD_FedFunds",
      Frequency::Quarterly,
      CompositeCalendar(NewYorkCalendar(), LondonCalendar()),
      ModifiedFollowing(), Period(0, TimeUnit::b), Actual360(), averaged_ff, 1,
      0.00228125, true, date(2019, 4, 12), 0.0, Frequency::Quarterly,
      CompositeCalendar(NewYorkCalendar(), LondonCalendar()),
      ModifiedFollowing(), Period(0, TimeUnit::b), Actual360(), libor_3m_index,
      1, 0, true, date(2019, 4, 12), 0.0);

  std::cout.precision(15);

  std::cout << "OIS NPV: " << ois->Evaluate(market, "USD").amount << '\n';
  std::cout << "IRS NPV: " << irs->Evaluate(market, "USD").amount << '\n';
  std::cout << "OIS NPV: " << ois2->Evaluate(market, "USD").amount << '\n';
  std::cout << "IRS NPV: " << irs2->Evaluate(market, "USD").amount << '\n';
  std::cout << "OIS NPV: " << ois3->Evaluate(market, "USD").amount << '\n';
  std::cout << "FF Swap NPV: " << ff_swap->Evaluate(market, "USD").amount
            << '\n';
  return 0;
}