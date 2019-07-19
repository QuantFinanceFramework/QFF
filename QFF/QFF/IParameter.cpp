#include "IParameter.h"
#include <cmath>

namespace qff {
double IParameter::mean(double time1, double time2) const {
  double total = integral(time1, time2);
  return total / (time2 - time1);
}

double IParameter::rootMeanSquare(double time1, double time2) const {
  double total = sqrt(integralSquare(time1, time2));
  return total / (time2 - time1);
}
}  // namespace qff