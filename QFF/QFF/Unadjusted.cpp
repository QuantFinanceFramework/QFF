#include "Unadjusted.h"

namespace qff {
unique_ptr<IBusinessDayConvention> Unadjusted::Clone() const {
  return std::make_unique<Unadjusted>();
}

date Unadjusted::Adjust(const date& original_date,
                        const ICalendar& calendar) const {
  return original_date;
}
}  // namespace qff