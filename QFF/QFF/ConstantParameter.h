#pragma once
#include "IParameter.h"

namespace qff {
class ConstantParameter : public IParameter {
 public:
  ConstantParameter() = default;
  ConstantParameter(double value);

  ~ConstantParameter() = default;

  double operator[](double time) const override;
  double Integral(double time1, double time2) const override;
  double IntegralSquare(double time1, double time2) const override;

 private:
  double value_{};
  double valueSquare_{};
};
}  // namespace qff