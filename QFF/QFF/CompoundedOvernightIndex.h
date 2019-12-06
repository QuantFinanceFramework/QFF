#pragma once
#include <memory>
#include <string>
#include <vector>
#include "IBusinessDayConvention.h"
#include "ICalendar.h"
#include "IDayCounter.h"
#include "IIndex.h"
#include "Period.h"

namespace qff {
class CompoundedOvernightIndex : public IIndex {
 public:
  CompoundedOvernightIndex() = default;
  CompoundedOvernightIndex(std::string currency_code, std::string curve_name,
                           const IDayCounter& day_counter, Period fixing_lag,
                           Period publication_lag,
                           const ICalendar& fixing_calendar,
                           const IBusinessDayConvention& convention);

  std::unique_ptr<IIndex> Clone() const override;

  double GetRate(const boost::gregorian::date& accrual_start,
                 const boost::gregorian::date& accrual_end,
                 const IMarketData& market_data) const override;

 private:
  void GenerateDates(const boost::gregorian::date& accrual_start,
                     const boost::gregorian::date& accrual_end) const;

  std::string currency_code_;
  std::string curve_name_;
  std::unique_ptr<IDayCounter> day_counter_;
  Period fixing_lag_;
  Period publication_lag_;
  std::unique_ptr<ICalendar> fixing_calendar_;
  std::unique_ptr<IBusinessDayConvention> convention_;
  mutable std::vector<boost::gregorian::date> accrual_dates_;
  mutable std::vector<double> accrual_factors_;
  mutable std::vector<boost::gregorian::date> fixing_dates_;
};
}  // namespace qff