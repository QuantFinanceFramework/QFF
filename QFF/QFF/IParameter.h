#pragma once

namespace qff {
class IParameter {
 public:
  IParameter() = default;
  virtual ~IParameter() = default;

  virtual double operator[](double time) const = 0;
  virtual double integral(double time1, double time2) const = 0;
  virtual double integralSquare(double time1, double time2) const = 0;

  double mean(double time1, double time2) const;
  double rootMeanSquare(double time1, double time2) const;
};
}  // namespace qff
