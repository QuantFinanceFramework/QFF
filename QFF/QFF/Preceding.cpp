#include "Preceding.h"

namespace qff {
unique_ptr<IBusinessDayConvention> Preceding::clone() const {
  return std::make_unique<Preceding>();
}

date Preceding::adjust(const date& originalDate,
                       const ICalendar& calendar) const {
  if (calendar.isBusinessDay(originalDate)) return originalDate;
  auto tmpDate = originalDate;
  do {
    tmpDate -= boost::gregorian::days(1);
  } while (!calendar.isBusinessDay(tmpDate));
  return tmpDate;
}
}  // namespace qff