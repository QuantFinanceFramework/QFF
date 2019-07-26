#include "IParameter.h"
#include <cmath>

namespace qff {
double IParameter::Mean(double time1, double time2) const {
  const auto total = Integral(time1, time2);
  return total / (time2 - time1);
}

double IParameter::RootMeanSquare(double time1, double time2) const {
  const auto total = sqrt(IntegralSquare(time1, time2));
  return total / (time2 - time1);
}
}  // namespace qff