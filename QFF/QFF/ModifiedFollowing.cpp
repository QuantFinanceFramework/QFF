#include "ModifiedFollowing.h"
#include "Following.h"
#include "Preceding.h"

namespace qff {
unique_ptr<IBusinessDayConvention> ModifiedFollowing::clone() const {
  return std::make_unique<ModifiedFollowing>();
}

date ModifiedFollowing::adjust(const date& originalDate,
                               const ICalendar& calendar) const {
  auto following = std::make_unique<Following>();
  auto tmpDate = following->adjust(originalDate, calendar);
  if (tmpDate.month() == originalDate.month()) return tmpDate;
  auto preceding = std::make_unique<Preceding>();
  return preceding->adjust(originalDate, calendar);
}
}  // namespace qff