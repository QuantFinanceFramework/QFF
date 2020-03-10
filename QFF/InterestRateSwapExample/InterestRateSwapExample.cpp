#include <Actual360.h>
#include <Actual365.h>
#include <AveragedOvernightIndex.h>
#include <CalculateIrResult.h>
#include <CompositeCalendar.h>
#include <CompoundedOvernightIndex.h>
#include <CurveInterpolator.h>
#include <DiscountFactorCurve.h>
#include <IborIndex.h>
#include <Interpolation.h>
#include <LondonCalendar.h>
#include <ModifiedFollowing.h>
#include <NewYorkCalendar.h>
#include <PricingEnvironment.h>
#include <SwapScheduler.h>
#include <Thirty360Isda.h>
#include <ZeroRateCurve.h>

#include <memory>
#include <vector>

using namespace aad;
using namespace qff_a;
using boost::gregorian::date;
using std::map;
using std::string;
using std::unique_ptr;
using std::vector;

int main() {
  const date pricing_date{2020, 1, 31};

  auto interpolator = CurveInterpolator<a_double>{
      &ProductLinearInterpol<a_double>, &ProductLinearExtrapol<a_double>};
  const Actual365 day_counter{};

  vector ff_pillars{
      date(2020, 2, 3), date(2020, 2, 13), date(2020, 2, 20), date(2020, 3, 6),
      date(2020, 4, 8), date(2020, 5, 6),  date(2020, 6, 8),  date(2020, 7, 8),
      date(2020, 8, 6), date(2020, 11, 6), date(2021, 2, 8),  date(2021, 8, 4),
      date(2022, 2, 4), date(2023, 2, 6),  date(2024, 2, 5),  date(2025, 2, 4),
      date(2026, 2, 4), date(2027, 2, 4),  date(2028, 2, 4),  date(2029, 2, 5),
      date(2030, 2, 4), date(2032, 2, 4),  date(2035, 2, 5),  date(2040, 2, 6),
      date(2045, 2, 6), date(2050, 2, 4),  date(2060, 2, 4)};

  vector ff_zeros{0.0157142629201847, 0.0160406863209875, 0.0160824439348794,
                  0.0161134455264112, 0.0160416235621084, 0.0159570512563784,
                  0.0158228733810686, 0.0156275866647933, 0.0154711858102748,
                  0.0148764481371773, 0.0142306690193869, 0.0132755841877428,
                  0.0126999728943875, 0.0121777751396347, 0.0120243963064879,
                  0.012061471498624,  0.0122453808443152, 0.0124577010089707,
                  0.0127362002510347, 0.0130122544457647, 0.0133075208792979,
                  0.0138503783924619, 0.0144669449582222, 0.0150971255186208,
                  0.0153189459232633, 0.0153272725963219, 0.0152905184676551};

  std::vector<a_double> ff_zeros_a(size(ff_zeros));
  convert_collection(ff_zeros.begin(), ff_zeros.end(), ff_zeros_a.begin());

  auto ff_curve = std::make_unique<ZeroRateCurve<a_double>>(
      pricing_date, "USD_FF", day_counter, interpolator, std::move(ff_pillars),
      ff_zeros_a);

  vector libor3m_pillars{
      date(2020, 5, 4),   date(2020, 6, 18),  date(2020, 9, 17),
      date(2020, 12, 16), date(2021, 3, 16),  date(2021, 6, 17),
      date(2021, 9, 16),  date(2021, 12, 15), date(2022, 3, 15),
      date(2022, 6, 16),  date(2022, 9, 15),  date(2022, 12, 21),
      date(2023, 3, 21),  date(2024, 2, 6),   date(2025, 2, 4),
      date(2026, 2, 4),   date(2027, 2, 4),   date(2028, 2, 4),
      date(2029, 2, 6),   date(2030, 2, 5),   date(2032, 2, 4),
      date(2035, 2, 6),   date(2040, 2, 6),   date(2045, 2, 6),
      date(2050, 2, 4),   date(2060, 2, 4)};

  vector libor3m_zeros{
      0.0178381083493583, 0.0173969812276502, 0.0168642145140453,
      0.016289592662108,  0.0158679325431119, 0.0153823991234107,
      0.0150126372200794, 0.0147145816665658, 0.0145246258808826,
      0.0143506404390577, 0.0142273222259718, 0.0141323537142728,
      0.0140837805673723, 0.0139972646586653, 0.0140599580931725,
      0.0142562020820564, 0.0144740641410424, 0.0147642468871795,
      0.0150532567844303, 0.0153470803109129, 0.0158999075443918,
      0.0165137979181888, 0.0171474776654111, 0.0173679270402262,
      0.0173759527633301, 0.017339032984036};

  std::vector<a_double> libor3m_zeros_a(size(libor3m_zeros));
  convert_collection(libor3m_zeros.begin(), libor3m_zeros.end(),
                     libor3m_zeros_a.begin());

  auto libor3m_curve = std::make_unique<ZeroRateCurve<a_double>>(
      pricing_date, "USD_LIBOR_3M", day_counter, interpolator,
      std::move(libor3m_pillars), libor3m_zeros_a);

  map<string, unique_ptr<IInterestRateCurve<a_double>>> curve_set;
  curve_set.emplace(std::make_pair("USD_FF", std::move(ff_curve)));
  curve_set.emplace(std::make_pair("USD_LIBOR_3M", std::move(libor3m_curve)));

  map<string, unique_ptr<ICreditCurve<a_double>>> credit_curve_set;

  map<string, map<date, double>> past_fixing_set{
      std::make_pair("USD_FF", map{std::make_pair(date(2020, 1, 27), 0.0155),
                                   std::make_pair(date(2020, 1, 28), 0.0155),
                                   std::make_pair(date(2020, 1, 29), 0.0155),
                                   std::make_pair(date(2020, 1, 30), 0.016)}),
      std::make_pair("USD_LIBOR_3M",
                     map{std::make_pair(date(2020, 1, 27), 0.017745),
                         std::make_pair(date(2020, 1, 28), 0.017695),
                         std::make_pair(date(2020, 1, 29), 0.0177713),
                         std::make_pair(date(2020, 1, 30), 0.0176325),
                         std::make_pair(date(2020, 1, 31), 0.0175113)})};

  const PricingEnvironment environment{pricing_date, std::move(curve_set),
                                       std::move(past_fixing_set),
                                       std::move(credit_curve_set)};

  CompoundedOvernightIndex ff_compounded_index{"USD",
                                               "USD_FF",
                                               Actual360(),
                                               Period(0, TimeUnit::b),
                                               Period(1, TimeUnit::b),
                                               NewYorkCalendar(),
                                               ModifiedFollowing()};

  auto ois = SwapScheduler::MakeInterestRateSwap(
      "USD", 10000000.0, date(2020, 2, 4), date(2023, 2, 4), false, "USD_FF",
      Frequency::Annually, NewYorkCalendar(), ModifiedFollowing(),
      Period(2, TimeUnit::b), Actual360(), 0.012093142296278,
      Frequency::Annually, NewYorkCalendar(), ModifiedFollowing(),
      Period(2, TimeUnit::b), Actual360(), ff_compounded_index, 1, 0.0, true,
      date(2020, 2, 4), 0.0);

  std::cout.precision(15);

  auto ois_result = CalculateIrResult(*ois, environment, "USD");

  std::cout << "OIS NPV = " << ois_result.GetNpv() << '\n';
  std::cout << '\n';

  std::cout << "OIS Zero Deltas : " << '\n';
  ois_result.PrintDeltas();
  std::cout << '\n';

  IborIndex ibor_index{"USD",
                       "USD_LIBOR_3M",
                       Actual360(),
                       Period(-2, TimeUnit::b),
                       LondonCalendar(),
                       ModifiedFollowing(),
                       Period(3, TimeUnit::m)};

  auto irs = SwapScheduler::MakeInterestRateSwap(
      "USD", 10000000.0, date(2020, 2, 4), date(2023, 2, 4), false, "USD_FF",
      Frequency::Semiannually,
      CompositeCalendar(NewYorkCalendar(), LondonCalendar()),
      ModifiedFollowing(), Period(0, TimeUnit::b), Thirty360Isda(), 0.015,
      Frequency::Quarterly,
      CompositeCalendar(NewYorkCalendar(), LondonCalendar()),
      ModifiedFollowing(), Period(0, TimeUnit::b), Actual360(), ibor_index, 1,
      0.0, true, date(2020, 2, 4), 0.0);

  auto irs_result = CalculateIrResult(*irs, environment, "USD");

  std::cout << "IRS NPV = " << irs_result.GetNpv() << '\n';
  std::cout << '\n';

  std::cout << "IRS Zero Deltas : " << '\n';
  irs_result.PrintDeltas();
  std::cout << '\n';

  return 0;
}