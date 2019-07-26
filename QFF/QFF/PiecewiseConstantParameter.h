#pragma once
#include <map>
#include "IParameter.h"

namespace qff {
using std::map;

class PiecewiseConstantParameter : public IParameter {
 public:
  PiecewiseConstantParameter() = default;
  PiecewiseConstantParameter(const map<double, double>& value);

  ~PiecewiseConstantParameter() = default;

  double operator[](double time) const override;
  double Integral(double time1, double time2) const override;
  double IntegralSquare(double time1, double time2) const override;

 private:
  map<double, double> value_;
};
}  // namespace qff