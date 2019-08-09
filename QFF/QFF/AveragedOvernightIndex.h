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
using std::string;
using std::unique_ptr;
using std::vector;

class AveragedOvernightIndex : public IIndex {
 public:
  AveragedOvernightIndex() = default;
  AveragedOvernightIndex(string currency_code, string curve_name,
                           const IDayCounter& day_counter, Period fixing_lag,
                           Period publication_lag,
                           const ICalendar& fixing_calendar,
                           const IBusinessDayConvention& convention,
                           Period rate_cut_off);

  ~AveragedOvernightIndex() = default;

  unique_ptr<IIndex> Clone() const override;

  double GetRate(const date& accrual_start, const date& accrual_end,
                 const IMarketData& market_data) const override;

 private:
  date GetFixingDate(const date& date) const;
  void GenerateRateDates(const date& first_date, const date& last_date) const;
  void GenerateFixingDates() const;
  void GenerateAccrualFactors() const;

  string currency_code_;
  string curve_name_;
  unique_ptr<IDayCounter> day_counter_;
  Period fixing_lag_{};
  Period publication_lag_{};
  unique_ptr<ICalendar> fixing_calendar_;
  unique_ptr<IBusinessDayConvention> convention_;
  Period rate_cut_off_;
  mutable vector<date> rate_dates_;
  mutable vector<date> fixing_dates_;
  mutable vector<double> accrual_factors_;
};
}  // namespace qff