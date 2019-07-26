#include "OvernightIndex.h"

namespace qff {
OvernightIndex::OvernightIndex(const string& currencyCode,
                               const string& curveName, Period tenor,
                               const IDayCounter& dayCounter, Period fixingLag,
                               Period publicationLag,
                               const ICalendar& fixingCalendar,
                               const IBusinessDayConvention& convention)
    : currencyCode_{currencyCode},
      curveName_{curveName},
      tenor_{tenor},
      dayCounter_(dayCounter.clone()),
      fixingLag_{fixingLag},
      publicationLag_{publicationLag},
      fixingCalendar_(fixingCalendar.clone()),
      convention_(convention.clone()) {}

unique_ptr<IIndex> OvernightIndex::clone() const {
  return unique_ptr<IIndex>();
}

double OvernightIndex::getRate(const date& startDate,
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

date OvernightIndex::getFixingDate(const date& startDate) const {
  return shiftDate(startDate, fixingLag_, *fixingCalendar_);
}
}  // namespace qff
