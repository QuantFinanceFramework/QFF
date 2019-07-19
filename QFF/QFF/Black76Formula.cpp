#include "Black76Formula.h"
#include <boost\math\distributions\normal.hpp>
#include <cmath>
#include <stdexcept>

namespace qff {
using boost::math::cdf;
using boost::math::normal;

double Black76Formula(double forwardPrice, double strike, double discountFactor,
                      double timeToMaturity, double volatility,
                      string optionType) {
  double d1 = (log(forwardPrice / strike) +
               0.5 * (volatility * volatility) * timeToMaturity) /
              (volatility * sqrt(timeToMaturity));
  double d2 = d1 - (volatility * sqrt(timeToMaturity));

  if (optionType == "call") {
    return discountFactor *
           (cdf(normal(), d1) * forwardPrice - cdf(normal(), d2) * strike);
  } else if (optionType == "put") {
    return discountFactor *
           (cdf(normal(), -d2) * strike - cdf(normal(), -d1) * forwardPrice);
  } else {
    // throw error?
    throw std::invalid_argument("invalid option type");
    // return 0;
  }
}
}  // namespace qff