#include "Unadjusted.h"

namespace qff {
unique_ptr<IBusinessDayConvention> Unadjusted::clone() const {
  return std::make_unique<Unadjusted>();
}

date Unadjusted::adjust(const date& originalDate,
                        const ICalendar& calendar) const {
  return originalDate;
}
}  // namespace qff