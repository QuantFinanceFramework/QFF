#include "CompoundedOvernightIndex.h"
#include <numeric>

namespace qff {
CompoundedOvernightIndex::CompoundedOvernightIndex(
    string currency_code, string curve_name, const IDayCounter& day_counter,
    Period fixing_lag, Period publication_lag, const ICalendar& fixing_calendar,
    const IBusinessDayConvention& convention)
    : currency_code_{std::move(currency_code)},
      curve_name_{std::move(curve_name)},
      day_counter_(day_counter.Clone()),
      fixing_lag_{fixing_lag},
      publication_lag_{publication_lag},
      fixing_calendar_(fixing_calendar.Clone()),
      convention_(convention.Clone()){};

unique_ptr<IIndex> CompoundedOvernightIndex::Clone() const {
  return std::make_unique<CompoundedOvernightIndex>(
      currency_code_, curve_name_, *day_counter_, fixing_lag_, publication_lag_,
      *fixing_calendar_, *convention_);
}

double CompoundedOvernightIndex::GetRate(const date& accrual_start,
                                         const date& accrual_end,
                                         const IMarketData& market_data) const {
  const auto year_fraction =
      day_counter_->CalculateYearFraction(accrual_start, accrual_end);
  const auto rate_start =
      ShiftDate(accrual_start, fixing_lag_, *fixing_calendar_);
  const auto rate_end = ShiftDate(accrual_end, fixing_lag_, *fixing_calendar_);

  if (rate_start > ShiftDate(market_data.GetMarketDate(), publication_lag_,
                             *fixing_calendar_)) {
    return (market_data.GetDiscountFactor(curve_name_, rate_start) /
                market_data.GetDiscountFactor(curve_name_, rate_end) -
            1.0) /
           year_fraction;
  }

  if (fixing_dates_.empty()) {
    GenerateDates(accrual_start, accrual_end);
  }

  const auto itr =
      std::upper_bound(fixing_dates_.begin(), fixing_dates_.end(),
                       ShiftDate(market_data.GetMarketDate(), -publication_lag_,
                                 *fixing_calendar_));

  const auto compounded_past_rate = std::transform_reduce(
      fixing_dates_.begin(), itr, accrual_factors_.begin(), 1.0,
      std::multiplies(), [&](auto fixing_date, auto factor) {
        return 1.0 +
               market_data.GetPastFixing(curve_name_, fixing_date) * factor;
      });
  return (compounded_past_rate *
              market_data.GetDiscountFactor(curve_name_, *itr) /
              market_data.GetDiscountFactor(curve_name_, accrual_end) -
          1.0) /
         year_fraction;
}

void CompoundedOvernightIndex::GenerateDates(const date& accrual_start,
                                             const date& accrual_end) const {
  accrual_dates_.clear();
  accrual_factors_.clear();
  fixing_dates_.clear();

  auto tmp_date = accrual_start;
  while (tmp_date < accrual_end) {
    accrual_dates_.emplace_back(tmp_date);
    tmp_date = ShiftDate(tmp_date, Period(1, TimeUnit::b), *fixing_calendar_);
  }

  accrual_factors_.reserve(size(accrual_dates_));
  std::transform(accrual_dates_.begin(), std::prev(accrual_dates_.end()),
                 std::next(accrual_dates_.begin()),
                 std::back_inserter(accrual_factors_), [&](auto s, auto e) {
                   return day_counter_->CalculateYearFraction(s, e);
                 });
  accrual_factors_.emplace_back(
      day_counter_->CalculateYearFraction(accrual_dates_.back(), accrual_end));

  fixing_dates_.reserve(size(accrual_dates_));
  std::transform(accrual_dates_.begin(), accrual_dates_.end(),
                 std::back_inserter(fixing_dates_), [&](auto date) {
                   return ShiftDate(date, fixing_lag_, *fixing_calendar_);
                 });
}
}  // namespace qff
