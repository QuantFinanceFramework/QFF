#pragma once
#include <memory>
#include <numeric>
#include <string>
#include <vector>

#include "DateFunctions.h"
#include "IBusinessDayConvention.h"
#include "ICalendar.h"
#include "IDayCounter.h"
#include "IIndex.h"
#include "Period.h"

namespace qff_a {
class CompoundedOvernightIndex final : public IIndex {
 public:
  CompoundedOvernightIndex(std::string currency_code, std::string curve_name,
                           const IDayCounter& day_counter, Period fixing_lag,
                           Period publication_lag,
                           const ICalendar& fixing_calendar,
                           const IBusinessDayConvention& convention);

  std::unique_ptr<IIndex> Clone() const override;

  double GetRate(
      const boost::gregorian::date& accrual_start,
      const boost::gregorian::date& accrual_end,
      const IPricingEnvironment<double>& pricing_environment) const override {
    return GetRateImpl(accrual_start, accrual_end, pricing_environment);
  }

  aad::a_double GetRate(const boost::gregorian::date& accrual_start,
                        const boost::gregorian::date& accrual_end,
                        const IPricingEnvironment<aad::a_double>&
                            pricing_environment) const override {
    return GetRateImpl(accrual_start, accrual_end, pricing_environment);
  }

 private:
  void GenerateDates(const boost::gregorian::date& accrual_start,
                     const boost::gregorian::date& accrual_end) const;

  template <typename T>
  T GetRateImpl(const boost::gregorian::date& accrual_start,
                const boost::gregorian::date& accrual_end,
                const IPricingEnvironment<T>& pricing_environment) const;

  std::string currency_code_;
  std::string curve_name_;
  std::unique_ptr<IDayCounter> day_counter_;
  Period fixing_lag_{};
  Period publication_lag_{};
  std::unique_ptr<ICalendar> fixing_calendar_;
  std::unique_ptr<IBusinessDayConvention> convention_;

  // Caching
  mutable std::vector<boost::gregorian::date> accrual_dates_;
  mutable std::vector<double> accrual_factors_;
  mutable std::vector<boost::gregorian::date> fixing_dates_;
};

inline CompoundedOvernightIndex::CompoundedOvernightIndex(
    std::string currency_code, std::string curve_name,
    const IDayCounter& day_counter, Period fixing_lag, Period publication_lag,
    const ICalendar& fixing_calendar, const IBusinessDayConvention& convention)
    : currency_code_{std::move(currency_code)},
      curve_name_{std::move(curve_name)},
      day_counter_(day_counter.Clone()),
      fixing_lag_{fixing_lag},
      publication_lag_{publication_lag},
      fixing_calendar_(fixing_calendar.Clone()),
      convention_(convention.Clone()) {}

inline std::unique_ptr<IIndex> CompoundedOvernightIndex::Clone() const {
  return std::make_unique<CompoundedOvernightIndex>(
      currency_code_, curve_name_, *day_counter_, fixing_lag_, publication_lag_,
      *fixing_calendar_, *convention_);
}

inline void CompoundedOvernightIndex::GenerateDates(
    const boost::gregorian::date& accrual_start,
    const boost::gregorian::date& accrual_end) const {
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

template <typename T>
T CompoundedOvernightIndex::GetRateImpl(
    const boost::gregorian::date& accrual_start,
    const boost::gregorian::date& accrual_end,
    const IPricingEnvironment<T>& pricing_environment) const {
  const auto year_fraction =
      day_counter_->CalculateYearFraction(accrual_start, accrual_end);
  const auto rate_start =
      ShiftDate(accrual_start, fixing_lag_, *fixing_calendar_);
  const auto rate_end = ShiftDate(accrual_end, fixing_lag_, *fixing_calendar_);

  if (rate_start > ShiftDate(pricing_environment.GetPricingDate(),
                             publication_lag_, *fixing_calendar_)) {
    return T((pricing_environment.GetDiscountFactor(curve_name_, rate_start) /
                  pricing_environment.GetDiscountFactor(curve_name_, rate_end) -
              1.0) /
             year_fraction);
  }

  if (fixing_dates_.empty()) {
    GenerateDates(accrual_start, accrual_end);
  }

  const auto itr =
      std::upper_bound(fixing_dates_.begin(), fixing_dates_.end(),
                       ShiftDate(pricing_environment.GetPricingDate(),
                                 -publication_lag_, *fixing_calendar_));

  const auto compounded_past_rate = std::transform_reduce(
      fixing_dates_.begin(), itr, accrual_factors_.begin(), 1.0,
      std::multiplies(), [&](auto fixing_date, auto factor) {
        return 1.0 +
               pricing_environment.GetPastRateFixing(curve_name_, fixing_date) *
                   factor;
      });
  return T(
      (compounded_past_rate *
           pricing_environment.GetDiscountFactor(curve_name_, *itr) /
           pricing_environment.GetDiscountFactor(curve_name_, accrual_end) -
       1.0) /
      year_fraction);
}
}  // namespace qff_a