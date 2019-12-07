#include <iostream>
#include <vector>
#include "Bond.h"
#include "DiscountCurve.h"
#include "ParametricCurve.h"

using namespace aad;

int main() {
  auto tape = *aad_double::tape;
  tape.clear();

  std::vector dfs{0.99, 0.97, 0.94};
  std::vector<aad_double> aad_dfs(3);
  convert_collection(dfs.begin(), dfs.end(), aad_dfs.begin());

  const DiscountCurve d{std::move(dfs)};
  const DiscountCurve d_aad{std::move(aad_dfs)};

  const Bond bond;

  const auto bond_result = bond.evaluate(d);
  std::cout << "NPV using DiscountCurve<double> = " << bond_result << '\n';
  auto adjoints = d.GetAdjoints();
  for (auto& a : adjoints) std::cout << "Adjoint (double)" << a << '\n';

  auto bond_result_aad = bond.evaluate(d_aad);
  bond_result_aad.propagate_to_start();
  std::cout << "NPV using DiscountCurve<aad_double> = "
            << bond_result_aad.value() << '\n';
  auto adjoints_aad = d_aad.GetAdjoints();
  for (auto& a : adjoints_aad) std::cout << "Adjoint (aad_double)" << a << '\n';

  tape.rewind();
  const ParametricCurve p{2.0, 10.0};
  const ParametricCurve p_aad{aad_double{2.0}, aad_double{10.0}};

  const auto bond_result_p = bond.evaluate(p);
  std::cout << "NPV using ParametricCurve<double> = " << bond_result_p << '\n';
  auto adjoints_p = p.GetAdjoints();
  for (auto& a : adjoints_p) std::cout << "Adjoint (double)" << a << '\n';

  auto bond_result_aad_p = bond.evaluate(p_aad);
  bond_result_aad_p.propagate_to_start();
  std::cout << "NPV using ParametricCurve<aad_double> = "
            << bond_result_aad_p.value() << '\n';
  auto adjoints_aad_p = p_aad.GetAdjoints();
  for (auto& a : adjoints_aad_p)
    std::cout << "Adjoint (aad_double)" << a << '\n';

  return EXIT_SUCCESS;
}
