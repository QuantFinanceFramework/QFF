#pragma once

#include <boost/math/distributions/normal.hpp>
#include <cmath>
#include <stdexcept>
#include <string_view>

#include "../Aad/aad_all.h"
#include "../include/dlib/source/dlib/optimization.h"

namespace qff_a {
template <typename T>
auto BlackScholesFormula(T spot, double strike, T discount_factor,
                         double time_to_maturity, T volatility,
                         const std::string_view option_type) {
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

// Use dlib::find_min_single_variable to solve the Black Scholes implied
// volatility from European option premium.
inline double BlackScholesImpliedVolatility(double premium, double spot,
                                            double strike,
                                            double discount_factor,
                                            double time_to_maturity,
                                            std::string_view option_type) {
  // initial guess
  auto guess{0.2};

  auto f = [&](const double vol) {
    return pow((BlackScholesFormula(spot, strike, discount_factor,
                                    time_to_maturity, vol, option_type) -
                premium),
               2);
  };

  dlib::find_min_single_variable(f, guess);

  return guess;
}
}  // namespace qff_a