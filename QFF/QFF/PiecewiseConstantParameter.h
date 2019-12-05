#pragma once
#include <map>
#include "IParameter.h"

namespace qff {

class PiecewiseConstantParameter : public IParameter {
 public:
  PiecewiseConstantParameter() = default;
  PiecewiseConstantParameter(std::map<double, double> value);

  double operator[](double time) const override;
  double Integral(double time1, double time2) const override;
  double IntegralSquare(double time1, double time2) const override;

 private:
  std::map<double, double> value_;
};
}  // namespace qff