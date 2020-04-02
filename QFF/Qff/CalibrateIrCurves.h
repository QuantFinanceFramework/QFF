#pragma once
#include <boost/range/combine.hpp>

#include "../include/dlib/source/dlib/matrix.h"
#include "../include/dlib/source/dlib/optimization.h"
#include "IProduct.h"
#include "PricingEnvironment.h"
#include "numeric"

namespace qff_a {
template <typename T>
void CalibrateIrCurves(
    PricingEnvironment<T>& environment,
    const std::vector<std::string>& curve_names,
    const std::vector<size_t>& pillar_numbers,
    const std::vector<std::shared_ptr<IProduct>>& instruments,
    const std::vector<boost::gregorian::date>& pillars,
    const std::vector<double>& initial_guesses) {
  // Number of parameters
  const auto n{size(initial_guesses)};

  // Initial guess
  dlib::matrix<double, 0, 1> zeros = dlib::mat(initial_guesses);

  auto pillar_itr = pillars.begin();
  for (auto [n, p] : boost::combine(curve_names, pillar_numbers)) {
    auto pillar_end = pillar_itr + p.head;
    environment.SetIrCurvePillars(n, {pillar_itr, pillar_end});
    pillar_itr = pillar_end;
  }

  // Objective function
  auto f = [&](const dlib::matrix<double, 0, 1>& input) {
    // Update InterestRateCurves in the PricingEnvironment
    std::vector<double> guess(input.begin(), input.end());
    auto itr = guess.begin();
    for (auto [n, p] : boost::combine(curve_names, pillar_numbers)) {
      auto end = itr + p.head;
      environment.SetIrCurveValues(n, {itr, end});
      itr = end;
    }

    // Mean squared error
    auto error = std::accumulate(instruments.begin(), instruments.end(), T(0.0),
                                 [&](auto result, auto& i) {
                                   auto npv =
                                       i->Evaluate(environment, "USD").amount;
                                   return T(result + npv * npv);
                                 });
    return error;
  };
  // BOBYQA (Bound Optimization BY Quadratic Approximation)
  dlib::find_min_bobyqa(
      f, zeros, n * 2, dlib::uniform_matrix<double>(n, 1, -0.05),
      dlib::uniform_matrix<double>(n, 1, 0.2), 0.1, 1e-13, n * 100);
}
}  // namespace qff_a
