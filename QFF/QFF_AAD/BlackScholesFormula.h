#pragma once

#include <boost/math/distributions/normal.hpp>
#include <cmath>
#include <stdexcept>
#include <string_view>

#include "../AAD/aad_all.h"
#include "../include/dlib/source/dlib/optimization.h"

namespace qff_a {
template <typename T>
auto BlackScholesFormula(T spot, double strike, T discount_factor,
                         double time_to_maturity, T volatility,
                         std::string_view option_type) {
  const auto d1 = (log(spot / strike) +
                   (-log(discount_factor) +
                    0.5 * volatility * volatility * time_to_maturity)) /
                  (volatility * sqrt(time_to_maturity));
  const auto d2 = d1 - (volatility * sqrt(time_to_maturity));

  if (option_type == "call") {
    return T(spot * aad::normal_cdf(d1) -
             discount_factor * strike * aad::normal_cdf(d2));
  }
  if (option_type == "put") {
    return T(discount_factor * strike * aad::normal_cdf(-d2) -
             spot * aad::normal_cdf(-d1));
  }
  throw std::invalid_argument("invalid option type");
}

inline double BlackScholesImpliedVolatility(double premium, double spot,
                                            double strike,
                                            double discount_factor,
                                            double time_to_maturity,
                                            std::string_view option_type) {
  // Initial guess
  dlib::matrix<double, 0, 1> vol = {0.5};
  auto search = dlib::bfgs_search_strategy();
  auto stop = dlib::objective_delta_stop_strategy(1e-7);

  auto f = [&](const dlib::matrix<double, 0, 1>& input) {
    return pow((BlackScholesFormula(spot, strike, discount_factor,
                                    time_to_maturity, input(0), option_type) -
                premium),
               2);
  };

  find_min_using_approximate_derivatives(search, stop, f, vol, 0.0);

  return vol(0);
}
}  // namespace qff_a