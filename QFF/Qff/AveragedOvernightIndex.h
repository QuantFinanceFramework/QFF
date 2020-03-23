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
class AveragedOvernightIndex final : public IIndex {
 public:
  AveragedOvernightIndex(std::string currency_code, std::string curve_name,
                         const IDayCounter& day_counter, Period fixing_lag,
                         Period publication_lag,
                         const ICalendar& fixing_calendar,
                         const IBusinessDayConvention& convention,
                         Period rate_cut_off, bool is_approximation);

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
  boost::gregorian::date GetFixingDate(
      const boost::gregorian::date& date) const;

  void GenerateDates(const boost::gregorian::date& accrual_start,
                     const boost::gregorian::date& accrual_end) const;

  template <typename T>
  T GetRateImpl(const boost::gregorian::date& accrual_start,
                const boost::gregorian::date& accrual_end,
                const IPricingEnvironment<T>& pricing_environment) const;

  std::string currency_code_;
  std::string curve_name_;
  std::unique_ptr<IDayCounter> day_counter_;
  Period fixing_lag_;
  Period publication_lag_;
  std::unique_ptr<ICalendar> fixing_calendar_;
  std::unique_ptr<IBusinessDayConvention> convention_;
  Period rate_cut_off_;
  bool is_approximation_;
  mutable std::vector<boost::gregorian::date> fixing_dates_;
  mutable std::vector<double> accrual_factors_;
};

inline AveragedOvernightIndex::AveragedOvernightIndex(
    std::string currency_code, std::string curve_name,
    const IDayCounter& day_counter, Period fixing_lag, Period publication_lag,
    const ICalendar& fixing_calendar, const IBusinessDayConvention& convention,
    Period rate_cut_off, bool is_approximation)
    : currency_code_{std::move(currency_code)},
      curve_name_{std::move(curve_name)},
      day_counter_(day_counter.Clone()),
      fixing_lag_{fixing_lag},
      publication_lag_{publication_lag},
      fixing_calendar_(fixing_calendar.Clone()),
      convention_(convention.Clone()),
      rate_cut_off_{rate_cut_off},
      is_approximation_(is_approximation) {}

inline std::unique_ptr<IIndex> AveragedOvernightIndex::Clone() const {
  return std::make_unique<AveragedOvernightIndex>(
      currency_code_, curve_name_, *day_counter_, fixing_lag_, publication_lag_,
      *fixing_calendar_, *convention_, rate_cut_off_, is_approximation_);
}

inline boost::gregorian::date AveragedOvernightIndex::GetFixingDate(
    const boost::gregorian::date& date) const {
  return ShiftDate(date, fixing_lag_, *fixing_calendar_);
}

inline void AveragedOvernightIndex::GenerateDates(
    const boost::gregorian::date& accrual_start,
    const boost::gregorian::date& accrual_end) const {
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

template <typename T>
T AveragedOvernightIndex::GetRateImpl(
    const boost::gregorian::date& accrual_start,
    const boost::gregorian::date& accrual_end,
    const IPricingEnvironment<T>& pricing_environment) const {
  const auto year_fraction =
      day_counter_->CalculateYearFraction(accrual_start, accrual_end);

  if (accrual_start > ShiftDate(pricing_environment.GetPricingDate(),
                                publication_lag_, *fixing_calendar_) &&
      is_approximation_) {
    return T(
        (log(pricing_environment.GetDiscountFactor(curve_name_,
                                                   accrual_start)) -
         log(pricing_environment.GetDiscountFactor(curve_name_, accrual_end))) /
        year_fraction);
  }

  if (fixing_dates_.empty()) {
    GenerateDates(accrual_start, accrual_end);
  }

  const auto itr =
      std::upper_bound(fixing_dates_.begin(), fixing_dates_.end(),
                       ShiftDate(pricing_environment.GetPricingDate(),
                                 -publication_lag_, *fixing_calendar_));

  const auto past_rate_sum = std::transform_reduce(
      fixing_dates_.begin(), itr, accrual_factors_.begin(), T(0.0), std::plus(),
      [&](auto fixing_date, auto factor) {
        return pricing_environment.GetPastRateFixing(curve_name_, fixing_date) *
               factor;
      });

  const auto future_rate_sum = std::transform_reduce(
      itr, std::prev(fixing_dates_.end()), std::next(itr), T(0.0), std::plus(),
      [&](auto s, auto e) {
        return (pricing_environment.GetDiscountFactor(curve_name_, s) /
                    pricing_environment.GetDiscountFactor(curve_name_, e) -
                1.0);
      });

  const auto last_fixing_start = fixing_dates_.back();
  const auto last_fixing_end = ShiftDate(
      fixing_dates_.back(), Period(1, TimeUnit::b), *fixing_calendar_);
  const auto last_year_fraction =
      day_counter_->CalculateYearFraction(last_fixing_start, last_fixing_end);

  const auto last_future_rate =
      (pricing_environment.GetDiscountFactor(curve_name_, last_fixing_start) /
           pricing_environment.GetDiscountFactor(curve_name_, last_fixing_end) -
       1.0) /
      last_year_fraction * accrual_factors_.back();

  return T((past_rate_sum + future_rate_sum + last_future_rate) /
           year_fraction);
}
}  // namespace qff_a