#pragma once
#include <functional>
#include "IInterpolator.h"
#include "Interpolation.h"

namespace qff {
class CurveInterpolator : public IInterpolator {
 public:
  CurveInterpolator() = default;

  CurveInterpolator(
      std::function<double(const double&, const std::map<double, double>&)>
          interpol_func,
      std::function<double(const double&, const std::map<double, double>&)>
          right_extrpol_func);

  double Interpol(const double& query_time,
                  const std::map<double, double>& data) const override;

  std::unique_ptr<IInterpolator> Clone() const override;

 private:
  std::function<double(const double&, const std::map<double, double>&)>
      interpol_func_ = LogLinearInterpol;
  std::function<double(const double&, const std::map<double, double>&)>
      right_extrapol_func_ = LogLinearExtrapol;
};
}  // namespace qff