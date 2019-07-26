#include "IborIndex.h"

namespace qff {
IborIndex::IborIndex(const string& currencyCode, const string& curveName,
                     Period tenor, const IDayCounter& dayCounter,
                     Period fixingLag,
                     const ICalendar& fixingCalendar,
                     const IBusinessDayConvention& convention,
                      bool preserveEndofMonth)
    : currencyCode_{currencyCode},
      curveName_{curveName},
      tenor_{tenor},
      dayCounter_(dayCounter.clone()),
      fixingLag_{fixingLag},
      fixingCalendar_(fixingCalendar.clone()),
      convention_(convention.clone()),
      preserveEndofMonth_{preserveEndofMonth} {}

unique_ptr<IIndex> IborIndex::clone() const { return unique_ptr<IIndex>(); }

double IborIndex::getRate(const date& startDate,
                          const IMarketData& marketData) const {
  const auto fixingDate = getFixingDate(startDate);

  if (fixingDate <= marketData.getMarketDate()) {
    return marketData.getPastFixing(curveName_, fixingDate);
  }
  const auto endDate =
      shiftDate(startDate, tenor_, *fixingCalendar_, *convention_);
  const auto yearFraction =
      dayCounter_->calculateYearFraction(startDate, endDate);

  return (marketData.getDiscountFactor(curveName_, startDate) /
              marketData.getDiscountFactor(curveName_, endDate) -
          1.0) /
         yearFraction;
}

date IborIndex::getFixingDate(const date& startDate) const {
  return shiftDate(startDate, fixingLag_, *fixingCalendar_);
}
}  // namespace qff
