#include <iostream>
#include <vector>

#include "Actual365.h"
#include "BlackScholesFormula.h"
#include "CurveInterpolator.h"
#include "DiscountFactorCurve.h"
#include "FixedCashflow.h"
#include "GenerateInterestRateDeltas.h"
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

  auto usd_std_df = std::make_unique<DiscountFactorCurve<double>>(
      market_date, Actual365{},
      CurveInterpolator<double>{&LogLinearInterpol<double>,
                                &LogLinearExtrapol<double>},
      pillars, dfs);

  map<string, unique_ptr<IInterestRateCurve<double>>> usd_curve_set;
  usd_curve_set.emplace("std", move(usd_std_df));

  map<string, unique_ptr<ICreditCurve<double>>> credit_curve_set;

  const auto environment = make_unique<PricingEnvironment<double>>(
      market_date, move(usd_curve_set), fixings, move(credit_curve_set));

  std::vector<a_double> aad_dfs(size(dfs));
  convert_collection(dfs.begin(), dfs.end(), aad_dfs.begin());

  auto usd_std_df_a = std::make_unique<DiscountFactorCurve<a_double>>(
      market_date, Actual365{},
      CurveInterpolator<a_double>{&LogLinearInterpol<a_double>,
                                  &LogLinearExtrapol<a_double>},
      pillars, aad_dfs);

  map<string, unique_ptr<IInterestRateCurve<a_double>>> usd_curve_set_a;
  usd_curve_set_a.emplace("std", move(usd_std_df_a));

  map<string, unique_ptr<ICreditCurve<a_double>>> credit_curve_set_a;

  const auto environment_a = make_unique<PricingEnvironment<a_double>>(
      market_date, move(usd_curve_set_a), fixings, move(credit_curve_set_a));

  const FixedCashflow instrument{100.0, date(2022, 4, 10), "std"};

  auto npv = instrument.Evaluate(*environment, "USD");

  auto adjoints = GenerateInterestRateDeltas(instrument, *environment_a, "USD");

  std::cout << "NPV = " << npv << '\n';

  std::cout << "DF Deltas:" << '\n';
  for (auto& i : adjoints)
    for (auto& d : i) {
      std::cout << d << '\n';
    }
  std::cout << '\n';

  std::vector zeros{0.02, 0.02, 0.021, 0.025};

  auto usd_std_z = std::make_unique<ZeroRateCurve<double>>(
      market_date, Actual365{},
      CurveInterpolator<double>{&ProductLinearInterpol<double>,
                                &ProductLinearExtrapol<double>},
      pillars, zeros);

  map<string, unique_ptr<IInterestRateCurve<double>>> usd_curve_set_z;

  usd_curve_set_z.emplace("std", move(usd_std_z));

  map<string, unique_ptr<ICreditCurve<double>>> credit_curve_set_z;

  const auto environment_z = make_unique<PricingEnvironment<double>>(
      market_date, move(usd_curve_set_z), fixings, move(credit_curve_set_z));

  std::vector<a_double> aad_zeros(size(zeros));

  convert_collection(zeros.begin(), zeros.end(), aad_zeros.begin());

  auto usd_std_z_a = std::make_unique<ZeroRateCurve<a_double>>(
      market_date, Actual365{},
      CurveInterpolator<a_double>{&ProductLinearInterpol<a_double>,
                                  &ProductLinearExtrapol<a_double>},
      pillars, aad_zeros);

  map<string, unique_ptr<IInterestRateCurve<a_double>>> usd_curve_set_z_a;

  usd_curve_set_z_a.emplace("std", move(usd_std_z_a));

  map<string, unique_ptr<ICreditCurve<a_double>>> credit_curve_set_z_a;

  const auto environment_z_a = make_unique<PricingEnvironment<a_double>>(
      market_date, move(usd_curve_set_z_a), fixings,
      move(credit_curve_set_z_a));

  auto npv_z = instrument.Evaluate(*environment_z, "USD");
  auto adjoints_z =
      GenerateInterestRateDeltas(instrument, *environment_z_a, "USD");

  std::cout << "NPV = " << npv << '\n';

  std::cout << "Zero Deltas:" << '\n';
  for (auto& i : adjoints_z)
    for (auto& d : i) {
      std::cout << d << '\n';
    }
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
