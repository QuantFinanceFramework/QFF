#include "CompositeCalendar.h"
#include <algorithm>

namespace qff {
CompositeCalendar::CompositeCalendar(vector<unique_ptr<ICalendar>> calendarList)
    : calendarList_(std::move(calendarList)) {}

unique_ptr<ICalendar> CompositeCalendar::clone() {
  vector<unique_ptr<ICalendar>> calendarList(sizeof(calendarList_));
  std::transform(calendarList_.begin(), calendarList_.end(),
                 calendarList.begin(), [](const auto& p) { return p->clone(); });
  return std::make_unique<CompositeCalendar>(std::move(calendarList));
}

bool CompositeCalendar::isHoliday(const date& queryDate) const {
  for (const auto& i : calendarList_) {
    if (i->isHoliday(queryDate)) return true;
  }
  return false;
}
}  // namespace qff
