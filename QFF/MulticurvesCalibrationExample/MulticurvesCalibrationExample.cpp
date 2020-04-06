#include <Actual365.h>
#include <AveragedOvernightIndex.h>
#include <CalibrateIrCurves.h>
#include <CompoundedOvernightIndex.h>
#include <CurveInterpolator.h>
#include <Interpolation.h>
#include <NewYorkFedCalendar.h>
#include <Period.h>
#include <ProductGenerator.h>

#include <iostream>

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/range/combine.hpp"

using namespace std;
using namespace qff_a;
using boost::gregorian::date;

int main() {
  try {
    std::cout.precision(15);

    const date pricing_date{2020, 1, 31};
    const date settlement_date{
        ShiftDate(pricing_date, Period{2, TimeUnit::b}, NewYorkFedCalendar())};

    auto interpolator = CurveInterpolator<double>{
        &ProductLinearInterpol<double>, &ProductLinearExtrapol<double>};
    const Actual365 day_counter{};

    auto ff_curve = std::make_unique<ZeroRateCurve<double>>(
        pricing_date, "USD_FF", day_counter, interpolator);

    auto libor_3m_curve = std::make_unique<ZeroRateCurve<double>>(
        pricing_date, "USD_LIBOR_3M", day_counter, interpolator);

    map<string, unique_ptr<IInterestRateCurve<double>>> curve_set;
    curve_set.emplace(std::make_pair("USD_FF", std::move(ff_curve)));
    curve_set.emplace(
        std::make_pair("USD_LIBOR_3M", std::move(libor_3m_curve)));

    map<string, unique_ptr<ICreditCurve<double>>> credit_curve_set;

    map<string, map<date, double>> past_fixing_set{std::make_pair(
        "USD_LIBOR_3M", map{std::make_pair(date(2020, 1, 30), 0.0176325),
                            std::make_pair(date(2020, 1, 31), 0.0175113)})};

    map<string, double> fx_today_map;

    auto environment = std::make_unique<PricingEnvironment<double>>(
        pricing_date, std::move(curve_set), std::move(past_fixing_set),
        std::move(credit_curve_set), std::move(fx_today_map));

    auto notional = 1e7;

    vector<string> curve_names{"USD_FF", "USD_LIBOR_3M"};

    vector<date> ff_pillars{ShiftDate(settlement_date, Period(1, TimeUnit::m),
                                      NewYorkFedCalendar()),
                            ShiftDate(settlement_date, Period(2, TimeUnit::m),
                                      NewYorkFedCalendar()),
                            ShiftDate(settlement_date, Period(3, TimeUnit::m),
                                      NewYorkFedCalendar()),
                            ShiftDate(settlement_date, Period(6, TimeUnit::m),
                                      NewYorkFedCalendar()),
                            ShiftDate(settlement_date, Period(9, TimeUnit::m),
                                      NewYorkFedCalendar()),
                            ShiftDate(settlement_date, Period(1, TimeUnit::y),
                                      NewYorkFedCalendar()),
                            ShiftDate(settlement_date, Period(5, TimeUnit::y),
                                      NewYorkFedCalendar()),
                            ShiftDate(settlement_date, Period(10, TimeUnit::y),
                                      NewYorkFedCalendar()),
                            ShiftDate(settlement_date, Period(20, TimeUnit::y),
                                      NewYorkFedCalendar()),
                            ShiftDate(settlement_date, Period(30, TimeUnit::y),
                                      NewYorkFedCalendar())};

    vector<string> ff_generators{"USSO", "USSO", "USSO", "USSO", "USSO",
                                 "USBG", "USBG", "USBG", "USBG", "USBG"};

    vector<double> ff_par_rates{0.01592,  0.01593,  0.01594,  0.01586,
                                0.01578,  0.001566, 0.001547, 0.001532,
                                0.001475, 0.001414};

    vector<shared_ptr<IProduct>> ff_instruments(size(ff_pillars));

    for (auto zipped : boost::combine(ff_instruments, ff_generators, ff_pillars,
                                      ff_par_rates)) {
      zipped.get<0>() = ProductGenerator::MakeProduct(
          zipped.get<1>(), notional, settlement_date, zipped.get<2>(),
          zipped.get<3>());
    }

    vector<date> libor_3m_pillars{
        date(2024, 2, 6), date(2025, 2, 4), date(2026, 2, 4), date(2027, 2, 4),
        date(2028, 2, 4), date(2029, 2, 6), date(2030, 2, 5), date(2032, 2, 4),
        date(2035, 2, 6), date(2040, 2, 6), date(2045, 2, 6), date(2050, 2, 4),
        date(2060, 2, 4)};

    vector<string> libor_3m_generators{
        "USSWAP", "USSWAP", "USSWAP", "USSWAP", "USSWAP", "USSWAP", "USSWAP",
        "USSWAP", "USSWAP", "USSWAP", "USSWAP", "USSWAP", "USSWAP"};

    vector<double> libor_3m_par_rates{
        0.0140538741, 0.014121,  0.0143107517, 0.0145215,    0.014801432,
        0.0150828333, 0.0153635, 0.0158885,    0.0164680902, 0.0170601804,
        0.0172779098, 0.0173075, 0.0173075};

    vector<shared_ptr<IProduct>> libor_3m_instruments(size(libor_3m_pillars));

    for (auto zipped : boost::combine(libor_3m_instruments, libor_3m_generators,
                                      libor_3m_pillars, libor_3m_par_rates)) {
      zipped.get<0>() = ProductGenerator::MakeProduct(
          zipped.get<1>(), notional, settlement_date, zipped.get<2>(),
          zipped.get<3>());
    }

    vector<date> pillars;
    std::copy(ff_pillars.begin(), ff_pillars.end(),
              std::back_inserter(pillars));
    std::copy(libor_3m_pillars.begin(), libor_3m_pillars.end(),
              std::back_inserter(pillars));

    vector<size_t> pillar_numbers{size(ff_pillars), size(libor_3m_pillars)};

    vector<shared_ptr<IProduct>> instruments;
    std::move(ff_instruments.begin(), ff_instruments.end(),
              std::back_inserter(instruments));
    std::move(libor_3m_instruments.begin(), libor_3m_instruments.end(),
              std::back_inserter(instruments));

    vector<double> initial_guesses(size(pillars));
    fill(initial_guesses.begin(), initial_guesses.end(), 0.02);

    CalibrateIrCurves(*environment, curve_names, pillar_numbers, instruments,
                      pillars, initial_guesses, "BFGS");

    cout << "USD_FF DF" << '\n';
    for (const auto& p : ff_pillars) {
      cout << environment->GetDiscountFactor("USD_FF", p) << '\n';
    }
    cout << '\n';

    cout << "USD_LIBOR_3M DF" << '\n';
    for (const auto& p : libor_3m_pillars) {
      cout << environment->GetDiscountFactor("USD_LIBOR_3M", p) << '\n';
    }
    cout << '\n';

    cout << "Calibration Instrument NPV:" << '\n';
    for (const auto& i : instruments) {
      cout << i->Evaluate(*environment, "USD").amount << '\n';
    }

  } catch (std::exception& e) {
    cout << e.what() << endl;
  }
  return 0;
}
