#include "CurveInterpolator.h"
#include <utility>

namespace qff {

unique_ptr<IInterpolator> CurveInterpolator::Clone() const {
  return std::make_unique<CurveInterpolator>(interpol_func_, right_extrapol_func_);
}

CurveInterpolator::CurveInterpolator(
    function<double(const double&, const map<double, double>&)> interpol_func,
    function<double(const double&, const map<double, double>&)>
        right_extrpol_func)
    : interpol_func_(interpol_func),
      right_extrapol_func_(right_extrpol_func) {}

double CurveInterpolator::Interpol(const double& query_time,
                                   const map<double, double>& data) const {
  if (query_time > std::prev(data.end())->first)
    return (right_extrapol_func_(query_time, data));
  return (interpol_func_(query_time, data));
}
}  // namespace qff