#include "CompositeCalendar.h"
#include <algorithm>

using boost::gregorian::date;
using std::unique_ptr;
using std::vector;

namespace qff {
CompositeCalendar::CompositeCalendar(
    vector<unique_ptr<ICalendar>> calendar_list)
    : calendar_list_(std::move(calendar_list)) {}

unique_ptr<ICalendar> CompositeCalendar::Clone() const {
  vector<unique_ptr<ICalendar>> calendarList(sizeof(calendar_list_));
  std::transform(calendar_list_.begin(), calendar_list_.end(),
                 calendarList.begin(),
                 [](const auto& p) { return p->Clone(); });
  return std::make_unique<CompositeCalendar>(std::move(calendarList));
}

bool CompositeCalendar::IsHoliday(const date& query_date) const {
  for (const auto& i : calendar_list_) {
    if (i->IsHoliday(query_date)) return true;
  }
  return false;
}
}  // namespace qff
