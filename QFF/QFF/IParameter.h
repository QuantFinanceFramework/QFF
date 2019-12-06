#pragma once

namespace qff {
class IParameter {
 public:
  virtual ~IParameter() = default;

  virtual double operator[](double time) const = 0;
  virtual double Integral(double time1, double time2) const = 0;
  virtual double IntegralSquare(double time1, double time2) const = 0;

  double Mean(double time1, double time2) const;
  double RootMeanSquare(double time1, double time2) const;
};
}  // namespace qff
