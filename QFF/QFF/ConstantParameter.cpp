#include "ConstantParameter.h"

namespace qff {
ConstantParameter::ConstantParameter(double value)
    : value_{value}, value_square_{value * value} {}

double ConstantParameter::operator[](double time) const { return value_; }

double ConstantParameter::Integral(double time1, double time2) const {
  return value_ * (time2 - time1);
}

double ConstantParameter::IntegralSquare(double time1, double time2) const {
  return value_square_ * (time2 - time1);
}
}  // namespace qff