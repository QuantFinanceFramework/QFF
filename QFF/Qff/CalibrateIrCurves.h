#pragma once
#include <boost/range/combine.hpp>
#include <numeric>
#include <stdexcept>
#include <string_view>

#include "../include/dlib/source/dlib/matrix.h"
#include "../include/dlib/source/dlib/optimization.h"
#include "IProduct.h"
#include "PricingEnvironment.h"

namespace qff_a {
inline void CalibrateIrCurves(
    PricingEnvironment<double>& environment,
    const std::vector<std::string>& curve_names,
    const std::vector<size_t>& pillar_numbers,
    const std::vector<std::shared_ptr<IProduct>>& instruments,
    const std::vector<boost::gregorian::date>& pillars,
    const std::vector<double>& initial_guesses,
    const std::string_view method = "BOBYQA") {
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

    return std::accumulate(
               instruments.begin(), instruments.end(), 0.0,
               [&](auto result, auto& i) {
                 return result + pow(i->Evaluate(environment, "USD").amount, 2);
               }) /
           (n * 1e7);
  };
  if (method == "BOBYQA") {
    // BOBYQA (Bound Optimization BY Quadratic Approximation)
    dlib::find_min_bobyqa(
        f, zeros, n * 2, dlib::uniform_matrix<double>(n, 1, -0.05),
        dlib::uniform_matrix<double>(n, 1, 0.2), 0.1, 1e-13, n * 100);
    return;
  }
  if (method == "BFGS") {
    // Broyden–Fletcher–Goldfarb–Shanno (BFGS) algorithm is an iterative method
    // for solving unconstrained nonlinear optimization problems.
    dlib::find_min_using_approximate_derivatives(
        dlib::lbfgs_search_strategy(n),
        dlib::objective_delta_stop_strategy(1e-15, 1000).be_verbose(), f, zeros,
        -1e-07);
    return;
  }
  throw std::invalid_argument("invalid method");
}
}  // namespace qff_a
