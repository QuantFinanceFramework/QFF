#pragma once
#include <functional>
#include "IInterpolator.h"
#include "Interpolation.h"

namespace qff {
using std::function;

class CurveInterpolator : public IInterpolator {
 public:
  CurveInterpolator() = default;

  CurveInterpolator(
      function<double(const double&, const map<double, double>&)> interpol_func,
      function<double(const double&, const map<double, double>&)>
          right_extrpol_func);

  ~CurveInterpolator() = default;

  double Interpol(const double& query_time,
                  const map<double, double>& data) const override;

  unique_ptr<IInterpolator> Clone() const override;

 private:
  function<double(const double&, const map<double, double>&)> interpol_func_ =
      LogLinearInterpol;
  function<double(const double&, const map<double, double>&)>
      right_extrapol_func_ = LogLinearExtrapol;
};
}  // namespace qff