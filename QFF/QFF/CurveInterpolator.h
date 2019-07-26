#pragma once
#include <functional>
#include "IInterpolator.h"

namespace qff {
using std::function;

class CurveInterpolator : public IInterpolator {
 public:
  CurveInterpolator() = default;

  ~CurveInterpolator() = default;

  double Interpol(const double& query_time,
                  const map<double, double>& data) const override;

 private:
  function<double(const double&, const map<double, double>&)>
      left_extrapol_func_;
  function<double(const double&, const map<double, double>&)> interpol_func_;
  function<double(const double&, const map<double, double>&)>
      right_extrapol_func_;
};
}  // namespace qff