#pragma once
#include <memory>
#include <string>
#include "IBusinessDayConvention.h"
#include "ICalendar.h"
#include "IDayCounter.h"
#include "IIndex.h"
#include "Period.h"

namespace qff {
class IborIndex : public IIndex {
 public:
  IborIndex() = default;
  IborIndex(std::string currency_code, std::string curve_name,
            const IDayCounter& day_counter, Period fixing_lag,
            const ICalendar& fixing_calendar,
            const IBusinessDayConvention& convention, Period tenor);

  std::unique_ptr<IIndex> Clone() const override;

  double GetRate(const boost::gregorian::date& accrual_start,
                 const boost::gregorian::date& accrual_end,
                 const IMarketData& market_data) const override;

 private:
  boost::gregorian::date GetFixingDate(
      const boost::gregorian::date& start_date) const;

  std::string currency_code_;
  std::string curve_name_;
  std::unique_ptr<IDayCounter> day_counter_;
  Period fixing_lag_;
  std::unique_ptr<ICalendar> fixing_calendar_;
  std::unique_ptr<IBusinessDayConvention> convention_;
  Period tenor_;
};
}  // namespace qff
