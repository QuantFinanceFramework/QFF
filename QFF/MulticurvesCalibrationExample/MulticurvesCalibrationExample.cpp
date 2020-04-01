#include <Actual360.h>
#include <Actual365.h>
#include <CalibrateIrCurves.h>
#include <CompositeCalendar.h>
#include <CompoundedOvernightIndex.h>
#include <CurveInterpolator.h>
#include <IborIndex.h>
#include <Interpolation.h>
#include <LondonCalendar.h>
#include <ModifiedFollowing.h>
#include <NewYorkFedCalendar.h>
#include <Period.h>
#include <SwapScheduler.h>
#include <Thirty360Isda.h>

#include <iostream>

#include "boost/date_time/gregorian/gregorian.hpp"

using namespace std;
using namespace qff_a;
using boost::gregorian::date;

int main() {
  try {
    const date pricing_date{2020, 1, 31};

    auto interpolator = CurveInterpolator<double>{
        &ProductLinearInterpol<double>, &ProductLinearExtrapol<double>};
    const Actual365 day_counter{};

    auto ff_curve = std::make_unique<ZeroRateCurve<double>>(
        pricing_date, "USD_FF", day_counter, interpolator);

    map<string, unique_ptr<IInterestRateCurve<double>>> curve_set;
    curve_set.emplace(std::make_pair("USD_FF", std::move(ff_curve)));

    map<string, unique_ptr<ICreditCurve<double>>> credit_curve_set;

    map<string, map<date, double>> past_fixing_set{};

    map<string, double> fx_today_map;

    auto environment = std::make_unique<PricingEnvironment<double>>(
        pricing_date, std::move(curve_set), std::move(past_fixing_set),
        std::move(credit_curve_set), std::move(fx_today_map));

    CompoundedOvernightIndex ff_compounded_index{"USD",
                                                 "USD_FF",
                                                 Actual360(),
                                                 Period(0, TimeUnit::b),
                                                 Period(1, TimeUnit::b),
                                                 NewYorkFedCalendar(),
                                                 ModifiedFollowing()};

    vector<shared_ptr<IProduct>> instruments{
        SwapScheduler::MakeInterestRateSwap(
            "USD", 10000000.0, date(2020, 2, 3), date(2021, 2, 3), false,
            "USD_FF", Frequency::Annually, NewYorkFedCalendar(),
            ModifiedFollowing(), Period(2, TimeUnit::b), Actual360(), 0.02,
            Frequency::Annually, NewYorkFedCalendar(), ModifiedFollowing(),
            Period(2, TimeUnit::b), Actual360(), ff_compounded_index, 1, 0.0,
            true, date(2020, 2, 3), 0.0),
        SwapScheduler::MakeInterestRateSwap(
            "USD", 10000000.0, date(2020, 2, 3), date(2030, 2, 3), false,
            "USD_FF", Frequency::Annually, NewYorkFedCalendar(),
            ModifiedFollowing(), Period(2, TimeUnit::b), Actual360(), 0.025,
            Frequency::Annually, NewYorkFedCalendar(), ModifiedFollowing(),
            Period(2, TimeUnit::b), Actual360(), ff_compounded_index, 1, 0.0,
            true, date(2020, 2, 3), 0.0),
        SwapScheduler::MakeInterestRateSwap(
            "USD", 10000000.0, date(2020, 2, 3), date(2040, 2, 3), false,
            "USD_FF", Frequency::Annually, NewYorkFedCalendar(),
            ModifiedFollowing(), Period(2, TimeUnit::b), Actual360(), 0.03,
            Frequency::Annually, NewYorkFedCalendar(), ModifiedFollowing(),
            Period(2, TimeUnit::b), Actual360(), ff_compounded_index, 1, 0.0,
            true, date(2020, 2, 3), 0.0)};

    vector<string> curve_names{"USD_FF"};
    vector<size_t> pillar_numbers{3};

    vector<date> pillars{date(2021, 2, 3), date(2030, 2, 3), date(2040, 2, 3)};
    vector<double> initial_guesses{0.02, 0.02, 0.02};

    CalibrateIrCurves(*environment, curve_names, pillar_numbers, instruments,
                      pillars, initial_guesses);

    cout << environment->GetDiscountFactor("USD_FF", date(2021, 2, 3)) << '\n';
    cout << environment->GetDiscountFactor("USD_FF", date(2030, 2, 3)) << '\n';
    cout << environment->GetDiscountFactor("USD_FF", date(2040, 2, 3)) << '\n';

    for (const auto& i : instruments) {
      cout << i->Evaluate(*environment, "USD").amount << '\n';
    }

  } catch (std::exception& e) {
    cout << e.what() << endl;
  }
  return 0;
}
