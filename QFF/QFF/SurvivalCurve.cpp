#include "SurvivalCurve.h"
#include <algorithm>
#include <cmath>
#include "DateFunctions.h"

namespace qff {
SurvivalCurve::SurvivalCurve(date curve_date, vector<date> dates,
                             const vector<double>& survival_probabilities,
                             const IInterpolator& interpolator,
                             const IDayCounter& day_counter)
    : curve_date_(curve_date),
      dates_(std::move(dates)),
      interpolator_(interpolator.Clone()),
      day_counter_(day_counter.Clone()) {
  std::transform(dates_.begin(), dates_.end(), survival_probabilities.begin(),
                 std::inserter(survival_probabilities_map_,
                               survival_probabilities_map_.end()),
                 [&](auto date, auto survival_probability) {
                   return std::make_pair(
                       DateToTime(*day_counter_, curve_date_, date),
                       survival_probability);
                 });
}

SurvivalCurve::SurvivalCurve(date&& curve_date, vector<date>&& dates,
                             map<double, double>&& survival_probabilities_map,
                             unique_ptr<IInterpolator> interpolator,
                             unique_ptr<IDayCounter> day_counter)
    : curve_date_(curve_date),
      dates_(dates),
      survival_probabilities_map_(survival_probabilities_map),
      interpolator_(std::move(interpolator)),
      day_counter_(std::move(day_counter)) {}

date SurvivalCurve::GetCurveDate() const { return curve_date_; }

double SurvivalCurve::GetSurvivalProbability(const date& query_date) const {
  return GetSurvivalProbability(
      DateToTime(*day_counter_, curve_date_, query_date));
}
double SurvivalCurve::GetSurvivalProbability(double query_time) const {
  return interpolator_->Interpol(query_time, survival_probabilities_map_);
}
}  // namespace qff
