#include "IborIndex.h"

using boost::gregorian::date;
using std::string;
using std::unique_ptr;

namespace qff {
IborIndex::IborIndex(string currency_code, string curve_name,
                     const IDayCounter& day_counter, Period fixing_lag,
                     const ICalendar& fixing_calendar,
                     const IBusinessDayConvention& convention, Period tenor)
    : currency_code_{std::move(currency_code)},
      curve_name_{std::move(curve_name)},
      day_counter_(day_counter.Clone()),
      fixing_lag_{fixing_lag},
      fixing_calendar_(fixing_calendar.Clone()),
      convention_(convention.Clone()),
      tenor_(tenor) {}

unique_ptr<IIndex> IborIndex::Clone() const {
  return std::make_unique<IborIndex>(currency_code_, curve_name_, *day_counter_,
                                     fixing_lag_, *fixing_calendar_,
                                     *convention_, tenor_);
}

double IborIndex::GetRate(const date& accrual_start, const date& accrual_end,
                          const IMarketData& market_data) const {
  const auto fixing_date = GetFixingDate(accrual_start);

  if (fixing_date <= market_data.GetMarketDate()) {
    return market_data.GetPastFixing(curve_name_, fixing_date);
  }
  const auto forward_end_date =
      ShiftDate(accrual_start, tenor_, *fixing_calendar_, *convention_);
  const auto year_fraction =
      day_counter_->CalculateYearFraction(accrual_start, forward_end_date);

  return (market_data.GetDiscountFactor(curve_name_, accrual_start) /
              market_data.GetDiscountFactor(curve_name_, forward_end_date) -
          1.0) /
         year_fraction;
}

date IborIndex::GetFixingDate(const date& start_date) const {
  return ShiftDate(start_date, fixing_lag_, *fixing_calendar_);
}
}  // namespace qff
