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

class IborIndex : public IIndex {
 public:
  IborIndex() = default;
  IborIndex(const string& currency_code, const string& curve_name, Period tenor,
            const IDayCounter& day_counter, Period fixing_lag,
            const ICalendar& fixing_calendar,
            const IBusinessDayConvention& convention, bool preserve_end_of_month);

  ~IborIndex() = default;

  unique_ptr<IIndex> Clone() const override;

  double GetRate(const date& start_date,
                 const IMarketData& market_data) const override;

 private:
  date GetFixingDate(const date& start_date) const;

  string currency_code_;
  string curve_name_;
  Period tenor_;
  unique_ptr<IDayCounter> day_counter_;
  Period fixing_lag_;
  unique_ptr<ICalendar> fixing_calendar_;
  unique_ptr<IBusinessDayConvention> convention_;
  bool preserve_end_of_month_;
};
}  // namespace qff
