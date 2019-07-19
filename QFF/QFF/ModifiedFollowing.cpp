#include "ModifiedFollowing.h"

namespace qff {
date ModifiedFollowing::adjust(const date& originalDate,
                               const ICalendar& calendar) const {
  auto tmpDate = Following::adjust(originalDate, calendar);
  if (tmpDate.month() == originalDate.month()) return tmpDate;
  return Preceding::adjust(originalDate, calendar);
}
}  // namespace qff