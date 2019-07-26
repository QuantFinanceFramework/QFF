#include "CurveInterpolator.h"

namespace qff {
double CurveInterpolator::Interpol(const double& query_time,
                                   const map<double, double>& data) const {
  if (query_time < data.begin()->first)
    return (left_extrapol_func_(query_time, data));
  if (query_time > data.end()->first)
	  return (right_extrapol_func_(query_time, data));
  return (interpol_func_(query_time, data));
}
}  // namespace qff