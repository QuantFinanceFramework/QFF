#include "Unadjusted.h"

namespace qff {
date Unadjusted::adjust(const date& originalDate,
                        const ICalendar& calendar) const {
  return originalDate;
}
}  // namespace qff