#include "IborIndex.h"

namespace qff {
IborIndex::IborIndex(string curveName, Period tenor, Period fixingOffset,
                     const ICalendar& fixingCalendar,
                     const IBusinessDayConvention& convention,
                     const IDayCounter& dayCounter, bool preserveEndofMonth)
    : curveName_{curveName},
      tenor_{tenor},
      fixingOffset_{fixingOffset},
      fixingCalendar_(fixingCalendar.clone()),
      convention_(convention.clone()),
      dayCounter_(dayCounter.clone()),
      preserveEndofMonth_{preserveEndofMonth} {}

unique_ptr<IIndex> IborIndex::clone() const { return unique_ptr<IIndex>(); }

double IborIndex::getRate(const date& startDate,
                          const IMarketData& marketData) const {
  auto fixingDate = getFixingDate(startDate);

  if (fixingDate <= marketData.getMarketDate()) {
    return marketData.getPastFixing(curveName_, fixingDate);
  }
  auto endDate = shiftDate(startDate, tenor_, *fixingCalendar_, *convention_);
  auto yearFraction = dayCounter_->calculateYearFraction(startDate, endDate);

  return (marketData.getDiscountFactor(curveName_, startDate) /
              marketData.getDiscountFactor(curveName_, endDate) -
          1.0) /
         yearFraction;
}

date IborIndex::getFixingDate(const date& startDate) const {
  return shiftDate(startDate, fixingOffset_, *fixingCalendar_);
}
}  // namespace qff
