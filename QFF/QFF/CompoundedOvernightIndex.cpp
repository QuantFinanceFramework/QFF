#include "CompoundedOvernightIndex.h"
#include <numeric>

namespace qff {

CompoundedOvernightIndex::CompoundedOvernightIndex(
    string currency_code, string curve_name, const IDayCounter& day_counter,
    Period fixing_lag, Period publication_lag, const ICalendar& fixing_calendar,
    const IBusinessDayConvention& convention, Period rate_cut_off)
    : currency_code_{std::move(currency_code)},
      curve_name_{std::move(curve_name)},
      day_counter_(day_counter.Clone()),
      fixing_lag_{fixing_lag},
      publication_lag_{publication_lag},
      fixing_calendar_(fixing_calendar.Clone()),
      convention_(convention.Clone()),
      rate_cut_off_{rate_cut_off} {};

unique_ptr<IIndex> CompoundedOvernightIndex::Clone() const {
  return std::make_unique<CompoundedOvernightIndex>(
      currency_code_, curve_name_, *day_counter_, fixing_lag_, publication_lag_,
      *fixing_calendar_, *convention_, rate_cut_off_);
}

date CompoundedOvernightIndex::GetFixingDate(const date& date) const {
  return ShiftDate(date, fixing_lag_, *fixing_calendar_);
}

void CompoundedOvernightIndex::GenerateRateDates(const date& first_date,
                                                 const date& last_date) const {
  rate_dates_.clear();
  auto tmp_date = first_date;
  const auto cut_off_date =
      ShiftDate(last_date, rate_cut_off_, *fixing_calendar_);
  while (tmp_date <= cut_off_date) {
    rate_dates_.emplace_back(tmp_date);
    tmp_date = ShiftDate(tmp_date, Period(1, TimeUnit::b), *fixing_calendar_);
  }
  if (cut_off_date != last_date) rate_dates_.emplace_back(last_date);
}

void CompoundedOvernightIndex::GenerateFixingDates() const {
  fixing_dates_.clear();
  std::transform(rate_dates_.begin(), std::prev(rate_dates_.end()),
                 std::back_inserter(fixing_dates_), [&](auto s) {
                   return ShiftDate(s, fixing_lag_ + publication_lag_,
                                    *fixing_calendar_);
                 });
}

void CompoundedOvernightIndex::GenerateAccrualFactors() const {
  accrual_factors_.clear();
  accrual_factors_.reserve(size(rate_dates_) - 1);
  std::transform(rate_dates_.begin(), std::prev(rate_dates_.end()),
                 std::next(rate_dates_.begin()),
                 std::back_inserter(accrual_factors_), [&](auto s, auto e) {
                   return day_counter_->CalculateYearFraction(s, e);
                 });
}

double CompoundedOvernightIndex::GetRate(const date& accrual_start,
                                         const date& accrual_end,
                                         const IMarketData& market_data) const {
  if (rate_dates_.empty()) {
    GenerateRateDates(accrual_start, accrual_end);
    GenerateFixingDates();
    GenerateAccrualFactors();
  }

  const auto year_fraction =
      day_counter_->CalculateYearFraction(accrual_start, accrual_end);

  const auto itr = std::upper_bound(fixing_dates_.begin(), fixing_dates_.end(),
                                    market_data.GetMarketDate());

  if (itr == fixing_dates_.begin()) {
    return (market_data.GetDiscountFactor(curve_name_, accrual_start) /
                market_data.GetDiscountFactor(curve_name_, accrual_end) -
            1.0) /
           year_fraction;
  }
  const auto compounded_past_rate = std::transform_reduce(
      fixing_dates_.begin(), itr, accrual_factors_.begin(), 1.0,
      std::multiplies(), [&](auto fixing_date, auto factor) {
        return 1.0 +
               market_data.GetPastFixing(curve_name_, fixing_date) * factor;
      });
  return (compounded_past_rate *
              market_data.GetDiscountFactor(
                  curve_name_,
                  market_data.GetMarketDate()) /
              market_data.GetDiscountFactor(curve_name_, accrual_end) -
          1.0) /
         year_fraction;
}
}  // namespace qff
