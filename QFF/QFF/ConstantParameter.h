#pragma once
#include "IParameter.h"

namespace qff {
class ConstantParameter : public IParameter {
 public:
  ConstantParameter() = default;
  ConstantParameter(double value);

  ~ConstantParameter() = default;

  double operator[](double time) const override;
  double integral(double time1, double time2) const override;
  double integralSquare(double time1, double time2) const override;

 private:
  double m_value;
  double m_valueSquare;
};
}  // namespace qff