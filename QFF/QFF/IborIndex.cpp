#include "IborIndex.h"

namespace qff {
IborIndex::IborIndex(string curveName, Period tenor, Period fixingOffset,
                     const ICalendar& fixingCalendar,
                     const IBusinessDayConvention& convention,
                     bool preserveEndofMonth)
    : curveName_{curveName},
      tenor_{tenor},
      fixingOffset_{fixingOffset},
      fixingCalendar_(fixingCalendar.clone()),
      convention_(convention.clone()),
      preserveEndofMonth_{preserveEndofMonth} {}
unique_ptr<IIndex> IborIndex::clone() const { return unique_ptr<IIndex>(); }

double IborIndex::getRate(const date& startDate,
                          const IMarketData& marketData) const {
  return 0.0;
}
}  // namespace qff
