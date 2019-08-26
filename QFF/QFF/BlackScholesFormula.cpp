#include "BlackScholesFormula.h"
#include <boost/math/distributions/normal.hpp>
#include <cmath>
#include <stdexcept>

using boost::math::cdf;
using boost::math::normal;
using std::string_view;

namespace qff {

double BlackScholesFormula(double spot, double strike, double discount_factor,
                           double time_to_maturity, double volatility,
                           string_view option_type) {
  const auto d1 = (log(spot / strike) +
                   (-log(discount_factor) +
                    0.5 * volatility * volatility * time_to_maturity)) /
                  (volatility * sqrt(time_to_maturity));
  const auto d2 = d1 - (volatility * sqrt(time_to_maturity));

  if (option_type == "call") {
    return spot * cdf(normal(), d1) -
           discount_factor * strike * cdf(normal(), d2);
  }
  if (option_type == "put") {
    return discount_factor * strike * cdf(normal(), -d2) -
           spot * cdf(normal(), -d1);
  }
  // throw error?
  throw std::invalid_argument("invalid option type");
  // return 0;
}
}  // namespace qff