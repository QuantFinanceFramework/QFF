#include "Black76Formula.h"
#include <boost/math/distributions/normal.hpp>
#include <cmath>
#include <stdexcept>

using boost::math::cdf;
using boost::math::normal;
using std::string_view;

namespace qff {
double Black76Formula(double forward_price, double strike,
                      double discount_factor, double time_to_maturity,
                      double volatility, string_view option_type) {
  const auto d1 = (log(forward_price / strike) +
                   0.5 * (volatility * volatility) * time_to_maturity) /
                  (volatility * sqrt(time_to_maturity));
  const auto d2 = d1 - (volatility * sqrt(time_to_maturity));

  if (option_type == "call") {
    return discount_factor *
           (cdf(normal(), d1) * forward_price - cdf(normal(), d2) * strike);
  }
  if (option_type == "put") {
    return discount_factor *
           (cdf(normal(), -d2) * strike - cdf(normal(), -d1) * forward_price);
  }
  // throw error?
  throw std::invalid_argument("invalid option type");
  // return 0;
}
}  // namespace qff