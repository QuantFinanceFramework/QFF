#include <iostream>
#include <vector>

#include "Actual365.h"
#include "BlackScholesFormula.h"
#include "CurveInterpolator.h"
#include "DiscountFactorCurve.h"
#include "FixedCashflow.h"
#include "ZeroRateCurve.h"

using namespace aad;
using namespace qff_a;
using boost::gregorian::date;

int main() {
  auto tape = *a_double::tape;
  tape.clear();

  const std::vector pillars{date(2020, 4, 10), date(2022, 4, 10),
                            date(2024, 4, 10)};
  std::vector dfs{0.99, 0.97, 0.94};
  std::vector<a_double> aad_dfs(3);
  convert_collection(dfs.begin(), dfs.end(), aad_dfs.begin());

  const date market_date{2019, 4, 10};

  const DiscountFactorCurve d{market_date, Actual365{},
                              CurveInterpolator<double>{}, pillars, dfs};

  const DiscountFactorCurve d_aad{market_date, Actual365{},
                                  CurveInterpolator<a_double>{}, pillars,
                                  aad_dfs};

  const FixedCashflow instrument{100.0, date(2022, 4, 10)};

  const auto instrument_result = instrument.Evaluate(d);
  std::cout << "NPV using DiscountFactorCurve<double> = " << instrument_result
            << '\n';

  auto adjoints = d.GetAdjoints();
  for (auto& a : adjoints) std::cout << "Adjoint (double)" << a << '\n';

  auto instrument_result_aad = instrument.Evaluate(d_aad);
  instrument_result_aad.propagate_to_start();
  std::cout << "NPV using DiscountFactorCurve<a_double> = "
            << instrument_result_aad.value() << '\n';
  auto adjoints_aad = d_aad.GetAdjoints();
  for (auto& a : adjoints_aad) std::cout << "Adjoint (a_double)" << a << '\n';

  tape.rewind();

  std::vector zeros{0.02, 0.021, 0.022};
  std::vector<a_double> aad_zeros(3);
  convert_collection(zeros.begin(), zeros.end(), aad_zeros.begin());

  const ZeroRateCurve z{market_date, Actual365{}, CurveInterpolator<double>{},
                        pillars, zeros};

  const ZeroRateCurve z_aad{market_date, Actual365{},
                            CurveInterpolator<a_double>{}, pillars, aad_zeros};

  const auto instrument_result_z = instrument.Evaluate(z);
  std::cout << "NPV using ZeroRateCurve<double> = " << instrument_result_z
            << '\n';

  auto adjoints_z = z.GetAdjoints();
  for (auto& a : adjoints_z) std::cout << "Adjoint (double)" << a << '\n';

  auto instrument_result_aad_z = instrument.Evaluate(z_aad);
  instrument_result_aad_z.propagate_to_start();
  std::cout << "NPV using ZeroRateCurve<a_double> = "
            << instrument_result_aad_z.value() << '\n';
  auto adjoints_aad_z = z_aad.GetAdjoints();
  for (auto& a : adjoints_aad_z) std::cout << "Adjoint (a_double)" << a << '\n';

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
