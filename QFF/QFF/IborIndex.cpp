#include "IborIndex.h"
#include <utility>

namespace qff {
IborIndex::IborIndex(string currency_code, string curve_name,
                     Period tenor, const IDayCounter& day_counter,
                     Period fixing_lag,
                     const ICalendar& fixing_calendar,
                     const IBusinessDayConvention& convention)
    : currency_code_{std::move(currency_code)},
      curve_name_{std::move(curve_name)},
      tenor_{tenor},
      day_counter_(day_counter.Clone()),
      fixing_lag_{fixing_lag},
      fixing_calendar_(fixing_calendar.Clone()),
      convention_(convention.Clone()){}

unique_ptr<IIndex> IborIndex::Clone() const { return unique_ptr<IIndex>(); }

double IborIndex::GetRate(const date& start_date,
                          const IMarketData& market_data) const {
  const auto fixing_date = GetFixingDate(start_date);

  if (fixing_date <= market_data.GetMarketDate()) {
    return market_data.GetPastFixing(curve_name_, fixing_date);
  }
  const auto end_date =
      ShiftDate(start_date, tenor_, *fixing_calendar_, *convention_);
  const auto year_fraction =
      day_counter_->CalculateYearFraction(start_date, end_date);

  return (market_data.GetDiscountFactor(curve_name_, start_date) /
              market_data.GetDiscountFactor(curve_name_, end_date) -
          1.0) /
         year_fraction;
}

date IborIndex::GetFixingDate(const date& start_date) const {
  return ShiftDate(start_date, fixing_lag_, *fixing_calendar_);
}
}  // namespace qff
