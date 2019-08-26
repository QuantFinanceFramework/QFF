#include "FlatHazardRateCurve.h"
#include "DateFunctions.h"

using boost::gregorian::date;

namespace qff {
FlatHazardRateCurve::FlatHazardRateCurve(date curve_date, double hazard_rate,
                                         const IDayCounter& day_counter)
    : curve_date_(curve_date),
      hazard_rate_(hazard_rate),
      day_counter_(day_counter.Clone()) {}

date FlatHazardRateCurve::GetCurveDate() const { return curve_date_; }

double FlatHazardRateCurve::GetSurvivalProbability(
    const date& query_date) const {
  return GetSurvivalProbability(
      DateToTime(*day_counter_, curve_date_, query_date));
}

double FlatHazardRateCurve::GetSurvivalProbability(double query_time) const {
  return exp(-hazard_rate_ * query_time);
}
}  // namespace qff