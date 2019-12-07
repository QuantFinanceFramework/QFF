#pragma once
#include <vector>

template <typename T>
class ICurve {
 public:
  virtual ~ICurve() = default;

  virtual T GetDiscountFactor(size_t itr) const = 0;
  virtual std::vector<double> GetAdjoints() const = 0;
};
