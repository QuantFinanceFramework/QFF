#pragma once
#include <memory>
#include <string>
#include "IBusinessDayConvention.h"
#include "ICalendar.h"
#include "IDayCounter.h"
#include "IIndex.h"
#include "Period.h"
namespace qff {
using std::string;
using std::unique_ptr;

class OvernightIndex : public IIndex {
 public:
  OvernightIndex() = default;
  OvernightIndex(string currency_code, string curve_name, Period tenor,
                 const IDayCounter& day_counter, Period fixing_lag,
                 Period publication_lag, const ICalendar& fixing_calendar,
                 const IBusinessDayConvention& convention);

  ~OvernightIndex() = default;

  unique_ptr<IIndex> Clone() const override;

  double GetRate(const date& start_date,
                 const IMarketData& market_data) const override;

  date GetFixingDate(const date& start_date) const override;

 private:
  string currency_code_;
  string curve_name_;
  Period tenor_{};
  unique_ptr<IDayCounter> day_counter_;
  Period fixing_lag_{};
  Period publication_lag_{};
  unique_ptr<ICalendar> fixing_calendar_;
  unique_ptr<IBusinessDayConvention> convention_;
};
}  // namespace qff