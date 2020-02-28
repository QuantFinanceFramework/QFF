#pragma once
#include <memory>
#include <string>

#include "DateFunctions.h"
#include "IBusinessDayConvention.h"
#include "ICalendar.h"
#include "IDayCounter.h"
#include "IIndex.h"
#include "Period.h"

namespace qff_a {
class IborIndex final : public IIndex {
 public:
  IborIndex(std::string currency_code, std::string curve_name,
            const IDayCounter& day_counter, Period fixing_lag,
            const ICalendar& fixing_calendar,
            const IBusinessDayConvention& convention, Period tenor);

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
      const boost::gregorian::date& start_date) const;

  template <typename T>
  T GetRateImpl(const boost::gregorian::date& accrual_start,
                const boost::gregorian::date& accrual_end,
                const IPricingEnvironment<T>& pricing_environment) const;

  std::string currency_code_;
  std::string curve_name_;
  std::unique_ptr<IDayCounter> day_counter_;
  Period fixing_lag_;
  std::unique_ptr<ICalendar> fixing_calendar_;
  std::unique_ptr<IBusinessDayConvention> convention_;
  Period tenor_;
};

inline std::unique_ptr<IIndex> IborIndex::Clone() const {
  return std::make_unique<IborIndex>(currency_code_, curve_name_, *day_counter_,
                                     fixing_lag_, *fixing_calendar_,
                                     *convention_, tenor_);
}

inline boost::gregorian::date IborIndex::GetFixingDate(
    const boost::gregorian::date& start_date) const {
  return ShiftDate(start_date, fixing_lag_, *fixing_calendar_);
}

template <typename T>
T IborIndex::GetRateImpl(
    const boost::gregorian::date& accrual_start,
    const boost::gregorian::date& accrual_end,
    const IPricingEnvironment<T>& pricing_environment) const {
  const auto fixing_date = GetFixingDate(accrual_start);

  if (fixing_date <= pricing_environment.GetPricingDate()) {
    return T(pricing_environment.GetPastRateFixing(curve_name_, fixing_date));
  }
  const auto forward_end_date =
      ShiftDate(accrual_start, tenor_, *fixing_calendar_, *convention_);
  const auto year_fraction =
      day_counter_->CalculateYearFraction(accrual_start, forward_end_date);

  return T((pricing_environment.GetDiscountFactor(curve_name_, accrual_start) /
                pricing_environment.GetDiscountFactor(curve_name_,
                                                      forward_end_date) -
            1.0) /
           year_fraction);
}
}  // namespace qff_a