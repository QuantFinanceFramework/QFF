#include "DiscountFactorCurve.h"
#include <algorithm>
#include <cmath>
#include <utility>

namespace qff {
DiscountFactorCurve::DiscountFactorCurve(date curve_date, vector<date> dates,
                                         const vector<double>& discount_factors,
                                         const IInterpolator& interpolator,
                                         const IDayCounter& day_counter)
    : curve_date_(curve_date),
      dates_(std::move(dates)),
      interpolator_(interpolator.Clone()),
      day_counter_(day_counter.Clone()) {
  std::transform(
      dates_.begin(), dates_.end(), discount_factors.begin(),std::inserter(discount_factors_map_, discount_factors_map_.end()),
      [&](auto d, auto df) { return std::make_pair(this->DateToTime(d), df); });
}

date DiscountFactorCurve::GetCurveDate() const { return curve_date_; }

double DiscountFactorCurve::GetDiscountFactor(const date& query_date) const {
  return GetDiscountFactor(DateToTime(query_date));
}

double DiscountFactorCurve::GetDiscountFactor(double query_time) const {
  return interpolator_->Interpol(query_time, discount_factors_map_);
}

double DiscountFactorCurve::GetForwardRate(const date& start_date,
                                           const date& end_date) const {
  return GetForwardRate(DateToTime(start_date), DateToTime(end_date));
}

double DiscountFactorCurve::GetForwardRate(double start_time,
                                           double end_time) const {
  return -log(GetDiscountFactor(end_time) / GetDiscountFactor(start_time)) /
         (end_time - start_time);
}

double DiscountFactorCurve::GetZeroRate(const date& query_date) const {
  return GetZeroRate(DateToTime(query_date));
}

double DiscountFactorCurve::GetZeroRate(double query_time) const {
  return -log(GetDiscountFactor(query_time)) / query_time;
}

double DiscountFactorCurve::DateToTime(const date& date) const {
  return day_counter_->CalculateYearFraction(curve_date_, date);
}
}  // namespace qff