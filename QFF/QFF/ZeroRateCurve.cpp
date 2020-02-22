#include "ZeroRateCurve.h"

#include <algorithm>
#include <cmath>

#include "DateFunctions.h"

using boost::gregorian::date;
using std::map;
using std::unique_ptr;
using std::vector;

namespace qff {
ZeroRateCurve::ZeroRateCurve(date curve_date, std::vector<date> dates,
                             const std::vector<double>& zero_rates,
                             const IInterpolator& interpolator,
                             const IDayCounter& day_counter)
    : curve_date_(curve_date),
      dates_(std::move(dates)),
      interpolator_(interpolator.Clone()),
      day_counter_(day_counter.Clone()) {
  std::transform(dates_.begin(), dates_.end(), zero_rates.begin(),
                 std::inserter(zero_rates_map_, zero_rates_map_.end()),
                 [&](auto date, auto discount_factor) {
                   return std::make_pair(
                       DateToTime(*day_counter_, curve_date_, date),
                       discount_factor);
                 });
}

ZeroRateCurve::ZeroRateCurve(date&& curve_date, std::vector<date>&& dates,
                             std::map<double, double>&& zero_rates_map,
                             std::unique_ptr<IInterpolator> interpolator,
                             std::unique_ptr<IDayCounter> day_counter)
    : curve_date_(curve_date),
      dates_(dates),
      zero_rates_map_(zero_rates_map),
      interpolator_(std::move(interpolator)),
      day_counter_(std::move(day_counter)) {}

date ZeroRateCurve::GetCurveDate() const { return curve_date_; }

double ZeroRateCurve::GetDiscountFactor(const date& query_date) const {
  return GetDiscountFactor(DateToTime(*day_counter_, curve_date_, query_date));
}

double ZeroRateCurve::GetDiscountFactor(double query_time) const {
  return interpolator_->Interpol(query_time, zero_rates_map_);
}

double ZeroRateCurve::GetForwardRate(const date& start_date,
                                     const date& end_date) const {
  return GetForwardRate(DateToTime(*day_counter_, curve_date_, start_date),
                        DateToTime(*day_counter_, curve_date_, end_date));
}

double ZeroRateCurve::GetForwardRate(double start_time, double end_time) const {
  return -log(GetDiscountFactor(end_time) / GetDiscountFactor(start_time)) /
         (end_time - start_time);
}

double ZeroRateCurve::GetZeroRate(const date& query_date) const {
  return GetZeroRate(DateToTime(*day_counter_, curve_date_, query_date));
}

double ZeroRateCurve::GetZeroRate(double query_time) const {
  return -log(GetDiscountFactor(query_time)) / query_time;
}
}  // namespace qff
