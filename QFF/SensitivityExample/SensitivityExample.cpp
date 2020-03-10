#include <iostream>
#include <vector>

#include "Actual365.h"
#include "BlackScholesFormula.h"
#include "CalculateIrResult.h"
#include "CurveInterpolator.h"
#include "DiscountFactorCurve.h"
#include "FixedCashflow.h"
#include "Interpolation.h"
#include "PricingEnvironment.h"
#include "SurvivalCurve.h"
#include "ZeroRateCurve.h"

using namespace std;
using namespace aad;
using namespace qff_a;
using boost::gregorian::date;

int main() {
  const date market_date{2019, 4, 10};

  const std::vector pillars{date(2019, 4, 10), date(2020, 4, 10),
                            date(2022, 4, 10), date(2024, 4, 10)};

  map<std::string, std::map<boost::gregorian::date, double>> fixings{};

  std::vector dfs{1.0, 0.980144965261876, 0.938889453837808, 0.882376020877698};

  std::vector<a_double> aad_dfs(size(dfs));
  convert_collection(dfs.begin(), dfs.end(), aad_dfs.begin());

  auto usd_std_df_a = std::make_unique<DiscountFactorCurve<a_double>>(
      market_date, "USD_STD", Actual365{},
      CurveInterpolator<a_double>{&LogLinearInterpol<a_double>,
                                  &LogLinearExtrapol<a_double>},
      pillars, aad_dfs);

  map<string, unique_ptr<IInterestRateCurve<a_double>>> usd_curve_set_a;
  usd_curve_set_a.emplace("std", move(usd_std_df_a));

  map<string, unique_ptr<ICreditCurve<a_double>>> credit_curve_set_a;

  const auto environment_a = make_unique<PricingEnvironment<a_double>>(
      market_date, move(usd_curve_set_a), fixings, move(credit_curve_set_a));

  const FixedCashflow instrument{100.0, date(2022, 4, 10), "std"};

  std::cout.precision(15);

  auto result = CalculateIrResult(instrument, *environment_a, "EUR");

  std::cout << "NPV = " << result.GetNpv() << '\n';
  std::cout << "DF Deltas : " << '\n';
  result.PrintDeltas();
  std::cout << '\n';

  std::vector zeros{0.02, 0.02, 0.021, 0.025};

  std::vector<a_double> aad_zeros(size(zeros));

  convert_collection(zeros.begin(), zeros.end(), aad_zeros.begin());

  auto usd_std_z_a = std::make_unique<ZeroRateCurve<a_double>>(
      market_date, "USD_STD", Actual365{},
      CurveInterpolator<a_double>{&ProductLinearInterpol<a_double>,
                                  &ProductLinearExtrapol<a_double>},
      pillars, aad_zeros);

  map<string, unique_ptr<IInterestRateCurve<a_double>>> usd_curve_set_z_a;

  usd_curve_set_z_a.emplace("std", move(usd_std_z_a));

  map<string, unique_ptr<ICreditCurve<a_double>>> credit_curve_set_z_a;

  const auto environment_z_a = make_unique<PricingEnvironment<a_double>>(
      market_date, move(usd_curve_set_z_a), fixings,
      move(credit_curve_set_z_a));

  auto result_z = CalculateIrResult(instrument, *environment_z_a, "EUR");

  std::cout << "NPV = " << result_z.GetNpv() << '\n';
  std::cout << "Zero Deltas : " << '\n';
  result_z.PrintDeltas();
  std::cout << '\n';

  auto tape = *a_double::tape;

  tape.rewind();

  std::cout << "NPV = "
            << BlackScholesFormula(100.0, 100.0, 1.0, 1.0, 0.2, "call") << '\n';
  a_double spot{100.0};
  auto strike{100.0};
  a_double dis{1.0};
  a_double v{0.2};

  auto black_result = BlackScholesFormula(spot, strike, dis, 1.0, v, "call");
  std::cout << "NPV_AAD = " << black_result.value() << '\n';
  black_result.propagate_to_start();
  std::cout << "Delta = " << spot.adjoint() << '\n';
  std::cout << "Vega = " << v.adjoint() << '\n';

  tape.rewind();

  return EXIT_SUCCESS;
}
