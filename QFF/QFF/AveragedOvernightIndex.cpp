#include "AveragedOvernightIndex.h"
#include "numeric"
#include "DateFunctions.h"

using boost::gregorian::date;
using std::string;
using std::unique_ptr;

namespace qff {
AveragedOvernightIndex::AveragedOvernightIndex(
    string currency_code, string curve_name, const IDayCounter& day_counter,
    Period fixing_lag, Period publication_lag, const ICalendar& fixing_calendar,
    const IBusinessDayConvention& convention, Period rate_cut_off,
    bool is_approximation)
    : currency_code_{std::move(currency_code)},
      curve_name_{std::move(curve_name)},
      day_counter_(day_counter.Clone()),
      fixing_lag_{fixing_lag},
      publication_lag_{publication_lag},
      fixing_calendar_(fixing_calendar.Clone()),
      convention_(convention.Clone()),
      rate_cut_off_{rate_cut_off},
      is_approximation_(is_approximation){}

unique_ptr<IIndex> AveragedOvernightIndex::Clone() const {
  return std::make_unique<AveragedOvernightIndex>(
      currency_code_, curve_name_, *day_counter_, fixing_lag_, publication_lag_,
      *fixing_calendar_, *convention_, rate_cut_off_, is_approximation_);
}

double AveragedOvernightIndex::GetRate(const date& accrual_start,
                                       const date& accrual_end,
                                       const IMarketData& market_data) const {
  const auto year_fraction =
      day_counter_->CalculateYearFraction(accrual_start, accrual_end);

  if (accrual_start > ShiftDate(market_data.GetMarketDate(), publication_lag_,
                                *fixing_calendar_) &&
      is_approximation_) {
    return (log(market_data.GetDiscountFactor(curve_name_, accrual_start)) -
            log(market_data.GetDiscountFactor(curve_name_, accrual_end))) /
           year_fraction;
  }

  if (fixing_dates_.empty()) {
    GenerateDates(accrual_start, accrual_end);
  }

  const auto itr =
      std::upper_bound(fixing_dates_.begin(), fixing_dates_.end(),
                       ShiftDate(market_data.GetMarketDate(), -publication_lag_,
                                 *fixing_calendar_));

  const auto past_rate_sum = std::transform_reduce(
      fixing_dates_.begin(), itr, accrual_factors_.begin(), 0.0, std::plus(),
      [&](auto fixing_date, auto factor) {
        return market_data.GetPastFixing(curve_name_, fixing_date) * factor;
      });

  const auto future_rate_sum = std::transform_reduce(
      itr, std::prev(fixing_dates_.end()), std::next(itr), 0.0, std::plus(),
      [&](auto s, auto e) {
        return (market_data.GetDiscountFactor(curve_name_, s) /
                    market_data.GetDiscountFactor(curve_name_, e) -
                1.0);
      });

  const auto last_fixing_start = fixing_dates_.back();
  const auto last_fixing_end = ShiftDate(
      fixing_dates_.back(), Period(1, TimeUnit::b), *fixing_calendar_);
  const auto last_year_fraction =
      day_counter_->CalculateYearFraction(last_fixing_start, last_fixing_end);

  const auto last_future_rate =
      (market_data.GetDiscountFactor(curve_name_, last_fixing_start) /
           market_data.GetDiscountFactor(curve_name_, last_fixing_end) -
       1.0) /
      last_year_fraction * accrual_factors_.back();

  return (past_rate_sum + future_rate_sum + last_future_rate) / year_fraction;
}

date AveragedOvernightIndex::GetFixingDate(const date& date) const {
  return ShiftDate(date, fixing_lag_, *fixing_calendar_);
}

void AveragedOvernightIndex::GenerateDates(const date& accrual_start,
                                           const date& accrual_end) const {
  fixing_dates_.clear();
  accrual_factors_.clear();
  const auto cut_off_date =
      ShiftDate(accrual_end, rate_cut_off_, *fixing_calendar_);
  auto tmp_date = accrual_start;
  while (tmp_date <= cut_off_date) {
    fixing_dates_.emplace_back(tmp_date);
    tmp_date = ShiftDate(tmp_date, Period(1, TimeUnit::b), *fixing_calendar_);
  }
  accrual_factors_.reserve(size(fixing_dates_));
  std::transform(fixing_dates_.begin(), std::prev(fixing_dates_.end()),
                 std::next(fixing_dates_.begin()),
                 std::back_inserter(accrual_factors_), [&](auto s, auto e) {
                   return day_counter_->CalculateYearFraction(s, e);
                 });
  accrual_factors_.emplace_back(
      day_counter_->CalculateYearFraction(fixing_dates_.back(), accrual_end));
}
}  // namespace qff