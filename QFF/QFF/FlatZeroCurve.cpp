#include "FlatZeroCurve.h"

using boost::gregorian::date;

namespace qff {
FlatZeroCurve::FlatZeroCurve(date curve_date, double zero_rate, const IDayCounter& day_counter)
    : curve_date_(curve_date), zero_rate_(zero_rate), day_counter_(day_counter.Clone()) {}

date FlatZeroCurve::GetCurveDate() const { return curve_date_; }

double FlatZeroCurve::GetDiscountFactor(const date& query_date) const {
  return GetDiscountFactor(DateToTime(query_date));
}

double FlatZeroCurve::GetDiscountFactor(double query_time) const {
  return exp(-zero_rate_ * query_time);
}

double FlatZeroCurve::GetForwardRate(const date& start_date,
                                     const date& end_date) const {
  return GetForwardRate(DateToTime(start_date), DateToTime(end_date));
}

double FlatZeroCurve::GetForwardRate(double start_time, double end_time) const {
  return zero_rate_;
}

double FlatZeroCurve::GetZeroRate(const date& query_date) const {
  return GetZeroRate(DateToTime(query_date));
}

double FlatZeroCurve::GetZeroRate(double query_time) const {
  return zero_rate_;
}

double FlatZeroCurve::DateToTime(const date& date) const {
  return day_counter_->CalculateYearFraction(curve_date_, date);
}
}  // namespace qff
