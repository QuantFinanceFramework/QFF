#include <iostream>
#include <vector>

#include "Actual365.h"
#include "ConcreteInstrument.h"
#include "CurveInterpolator.h"
#include "DiscountFactorsCurve.h"

using namespace aad;
using namespace qff_a;
using boost::gregorian::date;

int main() {
  auto tape = *a_double::tape;
  tape.clear();

  std::vector pillars{date(2020, 4, 10), date(2022, 4, 10), date(2024, 4, 10)};
  std::vector dfs{0.99, 0.97, 0.94};
  std::vector<a_double> aad_dfs(3);
  convert_collection(dfs.begin(), dfs.end(), aad_dfs.begin());

  const date market_date{2019, 4, 10};

  const DiscountFactorsCurve d{market_date, Actual365{},
                                   CurveInterpolator<double>{}, pillars,
                                   dfs};

  const DiscountFactorsCurve d_aad{market_date, Actual365{},
                                   CurveInterpolator<a_double>{}, pillars,
                                   aad_dfs};

  const ConcreteInstrument instrument{100.0, {1.0, 2.0, 3.0}};

  const auto instrument_result = instrument.Evaluate(d);
  std::cout << "NPV using DiscountFactorsCurve<double> = " << instrument_result
            << '\n';

  auto adjoints = d.GetAdjoints();
  for (auto& a : adjoints) std::cout << "Adjoint (double)" << a << '\n';

  auto instrument_result_aad = instrument.Evaluate(d_aad);
  instrument_result_aad.propagate_to_start();
  std::cout << "NPV using DiscountFactorsCurve<a_double> = "
            << instrument_result_aad.value() << '\n';
  auto adjoints_aad = d_aad.GetAdjoints();
  for (auto& a : adjoints_aad) std::cout << "Adjoint (a_double)" << a << '\n';

  tape.rewind();
  return EXIT_SUCCESS;
}
