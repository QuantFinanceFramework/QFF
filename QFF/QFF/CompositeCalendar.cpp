#include "CompositeCalendar.h"
#include <algorithm>

namespace qff {
CompositeCalendar::CompositeCalendar(
    vector<unique_ptr<ICalendar>> calendarList)
    : calendarList_(std::move(calendarList)) {}

unique_ptr<ICalendar> CompositeCalendar::clone() {
  return unique_ptr<CompositeCalendar>();
}

bool CompositeCalendar::isHoliday(const date& queryDate) const {
  for (const auto& i : calendarList_) {
    if (i->isHoliday(queryDate)) return true;
  }
  return false;
}
}  // namespace qff
