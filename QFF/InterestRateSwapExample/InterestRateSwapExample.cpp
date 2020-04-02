#include <Actual360.h>
#include <AveragedOvernightIndex.h>
#include <CalculateIrResult.h>
#include <CompositeCalendar.h>
#include <CompoundedOvernightIndex.h>
#include <DiscountFactorCurve.h>
#include <IborIndex.h>
#include <Interpolation.h>
#include <LondonCalendar.h>
#include <ModifiedFollowing.h>
#include <NewYorkFedCalendar.h>
#include <SwapScheduler.h>
#include <Thirty360Isda.h>
#include <UsBondMarketCalendar.h>

#include <memory>
#include <vector>

#include "MakePricingEnvironment.h"

using namespace aad;
using namespace qff_a;
using boost::gregorian::date;
using std::map;
using std::string;
using std::unique_ptr;
using std::vector;

int main() {
  auto environment = MakePricingEnvironment();

  CompoundedOvernightIndex ff_compounded_index{"USD",
                                               "USD_FF",
                                               Actual360(),
                                               Period(0, TimeUnit::b),
                                               Period(1, TimeUnit::b),
                                               NewYorkFedCalendar(),
                                               ModifiedFollowing()};

  auto ois = SwapScheduler::MakeInterestRateSwap(
      "USD", 10000000.0, date(2020, 2, 4), date(2023, 2, 4), false, "USD_FF",
      Frequency::Annually, NewYorkFedCalendar(), ModifiedFollowing(),
      Period(2, TimeUnit::b), Actual360(), 0.012093142296278,
      Frequency::Annually, NewYorkFedCalendar(), ModifiedFollowing(),
      Period(2, TimeUnit::b), Actual360(), ff_compounded_index, 1, 0.0, true,
      date(2020, 2, 4), 0.0);

  auto ois_par = SwapScheduler::MakeInterestRateSwap(
      "USD", 10000000.0, date(2020, 2, 4), date(2023, 2, 4), false, "USD_FF",
      Frequency::Annually, NewYorkFedCalendar(), ModifiedFollowing(),
      Period(2, TimeUnit::b), Actual360(),
      ois->GetParRate(*environment).value(), Frequency::Annually,
      NewYorkFedCalendar(), ModifiedFollowing(), Period(2, TimeUnit::b),
      Actual360(), ff_compounded_index, 1, 0.0, true, date(2020, 2, 4), 0.0);

  std::cout.precision(15);

  auto ois_result = CalculateIrResult(*ois, *environment, "USD");
  auto ois_par_result = CalculateIrResult(*ois_par, *environment, "USD");

  std::cout << "OIS NPV in " << ois_result.GetResultCurrency() << " = "
            << ois_result.GetNpv() << '\n';
  std::cout << '\n';

  std::cout << "Par OIS NPV in " << ois_par_result.GetResultCurrency() << " = "
            << ois_par_result.GetNpv() << '\n';
  std::cout << '\n';

  std::cout << "3Y Par-rate = " << ois->GetParRate(*environment).value()
            << '\n';
  std::cout << '\n';

  std::cout << "BPV = " << ois->GetBasisPointValue(*environment).value()
            << '\n';
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
      CompositeCalendar(NewYorkFedCalendar(), LondonCalendar()),
      ModifiedFollowing(), Period(0, TimeUnit::b), Thirty360Isda(), 0.015,
      Frequency::Quarterly,
      CompositeCalendar(NewYorkFedCalendar(), LondonCalendar()),
      ModifiedFollowing(), Period(0, TimeUnit::b), Actual360(), ibor_index, 1,
      0.0, true, date(2020, 2, 4), 0.0);

  auto irs_par = SwapScheduler::MakeInterestRateSwap(
      "USD", 10000000.0, date(2020, 2, 4), date(2023, 2, 4), false, "USD_FF",
      Frequency::Semiannually,
      CompositeCalendar(NewYorkFedCalendar(), LondonCalendar()),
      ModifiedFollowing(), Period(0, TimeUnit::b), Thirty360Isda(),
      irs->GetParRate(*environment).value(), Frequency::Quarterly,
      CompositeCalendar(NewYorkFedCalendar(), LondonCalendar()),
      ModifiedFollowing(), Period(0, TimeUnit::b), Actual360(), ibor_index, 1,
      0.0, true, date(2020, 2, 4), 0.0);

  auto irs_result = CalculateIrResult(*irs, *environment, "USD");
  auto irs_par_result = CalculateIrResult(*irs_par, *environment, "USD");

  std::cout << "IRS NPV in " << irs_result.GetResultCurrency() << " = "
            << irs_result.GetNpv() << '\n';
  std::cout << '\n';

  std::cout << "Par IRS NPV in " << irs_par_result.GetResultCurrency() << " = "
            << irs_par_result.GetNpv() << '\n';
  std::cout << '\n';

  std::cout << "3Y Par-rate = " << irs->GetParRate(*environment).value()
            << '\n';
  std::cout << '\n';

  std::cout << "BPV = " << irs->GetBasisPointValue(*environment).value()
            << '\n';
  std::cout << '\n';

  std::cout << "IRS Zero Deltas : " << '\n';
  irs_result.PrintDeltas();
  std::cout << '\n';

  CompoundedOvernightIndex sofr_compounded_index{"USD",
                                                 "USD_SOFR",
                                                 Actual360(),
                                                 Period(0, TimeUnit::b),
                                                 Period(1, TimeUnit::b),
                                                 UsBondMarketCalendar(),
                                                 ModifiedFollowing()};

  auto sofr_ois = SwapScheduler::MakeInterestRateSwap(
      "USD", 10000000.0, date(2020, 2, 4), date(2030, 2, 4), true, "USD_FF",
      Frequency::Annually, NewYorkFedCalendar(), ModifiedFollowing(),
      Period(2, TimeUnit::b), Actual360(), 0.013, Frequency::Annually,
      NewYorkFedCalendar(), ModifiedFollowing(), Period(2, TimeUnit::b),
      Actual360(), sofr_compounded_index, 1, 0.0, true, date(2020, 2, 4), 0.0);

  auto sofr_ois_par = SwapScheduler::MakeInterestRateSwap(
      "USD", 10000000.0, date(2020, 2, 4), date(2030, 2, 4), true, "USD_FF",
      Frequency::Annually, NewYorkFedCalendar(), ModifiedFollowing(),
      Period(2, TimeUnit::b), Actual360(),
      sofr_ois->GetParRate(*environment).value(), Frequency::Annually,
      NewYorkFedCalendar(), ModifiedFollowing(), Period(2, TimeUnit::b),
      Actual360(), sofr_compounded_index, 1, 0.0, true, date(2020, 2, 4), 0.0);

  auto sofr_ois_result = CalculateIrResult(*sofr_ois, *environment, "USD");
  auto sofr_ois_par_result =
      CalculateIrResult(*sofr_ois_par, *environment, "USD");

  std::cout << "SOFR OIS NPV in " << sofr_ois_result.GetResultCurrency()
            << " = " << sofr_ois_result.GetNpv() << '\n';
  std::cout << '\n';

  std::cout << "Par SOFR OIS NPV in " << sofr_ois_par_result.GetResultCurrency()
            << " = " << sofr_ois_par_result.GetNpv() << '\n';
  std::cout << '\n';

  std::cout << "10Y SOFR Par-rate = "
            << sofr_ois->GetParRate(*environment).value() << '\n';
  std::cout << '\n';

  std::cout << "BPV = " << sofr_ois->GetBasisPointValue(*environment).value()
            << '\n';
  std::cout << '\n';

  std::cout << "SOFR OIS Zero Deltas : " << '\n';
  sofr_ois_result.PrintDeltas();
  std::cout << '\n';

  auto sofr_ff_basis = SwapScheduler::MakeBasisSwap(
      "USD", 10000000.0, date(2020, 2, 4), date(2023, 2, 4), "USD_FF",
      Frequency::Quarterly, NewYorkFedCalendar(), ModifiedFollowing(),
      Period(2, TimeUnit::b), Actual360(), sofr_compounded_index, 1.0,
      -0.000057, true, date(2020, 2, 4), 0.0, Frequency::Quarterly,
      NewYorkFedCalendar(), ModifiedFollowing(), Period(2, TimeUnit::b),
      Actual360(), ff_compounded_index, 1.0, true, date(2020, 2, 4), 0.0,
      false);

  auto sofr_ff_basis_par = SwapScheduler::MakeBasisSwap(
      "USD", 10000000.0, date(2020, 2, 4), date(2023, 2, 4), "USD_FF",
      Frequency::Quarterly, NewYorkFedCalendar(), ModifiedFollowing(),
      Period(2, TimeUnit::b), Actual360(), sofr_compounded_index, 1.0,
      sofr_ff_basis->GetParRate(*environment).value(), true, date(2020, 2, 4),
      0.0, Frequency::Quarterly, NewYorkFedCalendar(), ModifiedFollowing(),
      Period(2, TimeUnit::b), Actual360(), ff_compounded_index, 1.0, true,
      date(2020, 2, 4), 0.0, false);

  auto sofr_ff_basis_result =
      CalculateIrResult(*sofr_ff_basis, *environment, "USD");
  auto sofr_ff_basis_par_result =
      CalculateIrResult(*sofr_ff_basis_par, *environment, "USD");

  std::cout << "SOFR FF Basis NPV in "
            << sofr_ff_basis_result.GetResultCurrency() << " = "
            << sofr_ff_basis_result.GetNpv() << '\n';
  std::cout << '\n';

  std::cout << "Par SOFR FF Basis NPV in "
            << sofr_ff_basis_par_result.GetResultCurrency() << " = "
            << sofr_ff_basis_par_result.GetNpv() << '\n';
  std::cout << '\n';

  std::cout << "3Y SOFR FF Basis Par-rate = "
            << sofr_ff_basis->GetParRate(*environment).value() << '\n';
  std::cout << '\n';

  std::cout << "BPV = "
            << sofr_ff_basis->GetBasisPointValue(*environment).value() << '\n';
  std::cout << '\n';

  std::cout << "SOFR FF Basis Zero Deltas : " << '\n';
  sofr_ff_basis_result.PrintDeltas();
  std::cout << '\n';

  AveragedOvernightIndex ff_averaged_index{"USD",
                                           "USD_FF",
                                           Actual360(),
                                           Period(0, TimeUnit::b),
                                           Period(1, TimeUnit::b),
                                           NewYorkFedCalendar(),
                                           ModifiedFollowing(),
                                           Period(-2, TimeUnit::b),
                                           false};

  auto ff_libor_basis = SwapScheduler::MakeBasisSwap(
      "USD", 10000000.0, date(2020, 2, 4), date(2023, 2, 4), "USD_FF",
      Frequency::Quarterly, NewYorkFedCalendar(), ModifiedFollowing(),
      Period(0, TimeUnit::b), Actual360(), ff_averaged_index, 1.0, 0.002, true,
      date(2020, 2, 4), 0.0, Frequency::Quarterly, NewYorkFedCalendar(),
      ModifiedFollowing(), Period(0, TimeUnit::b), Actual360(), ibor_index, 1.0,
      true, date(2020, 2, 4), 0.0, false);

  auto ff_libor_basis_par = SwapScheduler::MakeBasisSwap(
      "USD", 10000000.0, date(2020, 2, 4), date(2023, 2, 4), "USD_FF",
      Frequency::Quarterly, NewYorkFedCalendar(), ModifiedFollowing(),
      Period(0, TimeUnit::b), Actual360(), ff_averaged_index, 1.0,
      ff_libor_basis->GetParRate(*environment).value(), true, date(2020, 2, 4),
      0.0, Frequency::Quarterly, NewYorkFedCalendar(), ModifiedFollowing(),
      Period(0, TimeUnit::b), Actual360(), ibor_index, 1.0, true,
      date(2020, 2, 4), 0.0, false);

  auto ff_libor_basis_result =
      CalculateIrResult(*ff_libor_basis, *environment, "USD");
  auto ff_libor_basis_par_result =
      CalculateIrResult(*ff_libor_basis_par, *environment, "USD");

  std::cout << "FF Swap NPV in " << ff_libor_basis_result.GetResultCurrency()
            << " = " << ff_libor_basis_result.GetNpv() << '\n';
  std::cout << '\n';

  std::cout << "Par FF Swap NPV in "
            << ff_libor_basis_par_result.GetResultCurrency() << " = "
            << ff_libor_basis_par_result.GetNpv() << '\n';
  std::cout << '\n';

  std::cout << "3Y FF Swap Par-rate = "
            << ff_libor_basis->GetParRate(*environment).value() << '\n';
  std::cout << '\n';

  std::cout << "BPV = "
            << ff_libor_basis->GetBasisPointValue(*environment).value() << '\n';
  std::cout << '\n';

  std::cout << "FF Swap Zero Deltas : " << '\n';
  ff_libor_basis_result.PrintDeltas();
  std::cout << '\n';

  return 0;
}
