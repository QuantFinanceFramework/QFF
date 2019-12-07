#pragma once
#include <vector>

template <typename T>
class ICurve {
 public:
  virtual ~ICurve() = default;

  virtual T GetDiscountFactor(double time) const = 0;
  virtual std::vector<double> GetAdjoints() const = 0;
};
