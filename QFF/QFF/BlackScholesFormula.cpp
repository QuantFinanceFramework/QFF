#include "BlackScholesFormula.h"
#include <boost\math\distributions\normal.hpp>
#include <cmath>
#include <stdexcept>

namespace qff {
using boost::math::cdf;
using boost::math::normal;

double BlackScholesFormula(double spot, double strike, double discountFactor,
                           double timeToMaturity, double volatility,
                           string optionType) {
  double d1 =
      (log(spot / strike) + (-log(discountFactor) +
                             0.5 * volatility * volatility * timeToMaturity)) /
      (volatility * sqrt(timeToMaturity));
  double d2 = d1 - (volatility * sqrt(timeToMaturity));

  if (optionType == "call") {
    return spot * cdf(normal(), d1) -
           discountFactor * strike * cdf(normal(), d2);
  } else if (optionType == "put") {
    return discountFactor * strike * cdf(normal(), -d2) -
           spot * cdf(normal(), -d1);
  } else {
    // throw error?
    throw std::invalid_argument("invalid option type");
    // return 0;
  }
}
}  // namespace qff