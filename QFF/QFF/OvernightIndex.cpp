#include "OvernightIndex.h"
#include <utility>

namespace qff {
OvernightIndex::OvernightIndex(string currency_code, string curve_name,
                               Period tenor, const IDayCounter& day_counter,
                               Period fixing_lag, Period publication_lag,
                               const ICalendar& fixing_calendar,
                               const IBusinessDayConvention& convention)
    : currency_code_{std::move(currency_code)},
      curve_name_{std::move(curve_name)},
      tenor_{tenor},
      day_counter_(day_counter.Clone()),
      fixing_lag_{fixing_lag},
      publication_lag_{publication_lag},
      fixing_calendar_(fixing_calendar.Clone()),
      convention_(convention.Clone()) {}

unique_ptr<IIndex> OvernightIndex::Clone() const {
  return std::make_unique<OvernightIndex>(
      currency_code_, curve_name_, tenor_, *day_counter_, fixing_lag_,
      publication_lag_, *fixing_calendar_, *convention_);
}

double OvernightIndex::GetRate(const date& start_date,
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

date OvernightIndex::GetFixingDate(const date& start_date) const {
  return ShiftDate(start_date, fixing_lag_ + publication_lag_,
                   *fixing_calendar_);
}
}  // namespace qff
