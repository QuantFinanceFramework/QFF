#include "AveragedOvernightIndex.h"
#include "numeric"

namespace qff {
AveragedOvernightIndex::AveragedOvernightIndex(
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

unique_ptr<IIndex> AveragedOvernightIndex::Clone() const {
  return std::make_unique<AveragedOvernightIndex>(
      currency_code_, curve_name_, *day_counter_, fixing_lag_, publication_lag_,
      *fixing_calendar_, *convention_, rate_cut_off_);
}

double AveragedOvernightIndex::GetRate(const date& accrual_start,
                                       const date& accrual_end,
                                       const IMarketData& market_data) const {
  if (rate_dates_.empty()) {
    GenerateRateDates(accrual_start, accrual_end);
    GenerateFixingDates();
    GenerateAccrualFactors();
  }

  const auto year_fraction =
      day_counter_->CalculateYearFraction(accrual_start, accrual_end);

  auto rate_sum = 0.0;

  for (auto i = 0; i < size(fixing_dates_); ++i) {
    if (fixing_dates_[i] < market_data.GetMarketDate()) {
      rate_sum += market_data.GetPastFixing(curve_name_, fixing_dates_[i]) *
                  accrual_factors_[i];
    }
    rate_sum +=
        (market_data.GetDiscountFactor(curve_name_, rate_dates_[i]) /
             market_data.GetDiscountFactor(curve_name_, rate_dates_[i + 1]) -
         1.0);
  }

  return rate_sum / year_fraction;
}

date AveragedOvernightIndex::GetFixingDate(const date& date) const {
  return ShiftDate(date, fixing_lag_, *fixing_calendar_);
}

void AveragedOvernightIndex::GenerateRateDates(const date& first_date,
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

void AveragedOvernightIndex::GenerateFixingDates() const {
  fixing_dates_.clear();
  std::transform(rate_dates_.begin(), std::prev(rate_dates_.end()),
                 std::back_inserter(fixing_dates_), [&](auto s) {
                   return ShiftDate(s, fixing_lag_ + publication_lag_,
                                    *fixing_calendar_);
                 });
}

void AveragedOvernightIndex::GenerateAccrualFactors() const {
  accrual_factors_.clear();
  accrual_factors_.reserve(size(rate_dates_) - 1);
  std::transform(rate_dates_.begin(), std::prev(rate_dates_.end()),
                 std::next(rate_dates_.begin()),
                 std::back_inserter(accrual_factors_), [&](auto s, auto e) {
                   return day_counter_->CalculateYearFraction(s, e);
                 });
}
}  // namespace qff