#include "BaseCalendar.h"

using boost::gregorian::date;
using std::unique_ptr;

namespace qff_a {
unique_ptr<ICalendar> BaseCalendar::Clone() const {
  return std::make_unique<BaseCalendar>(*this);
}

bool BaseCalendar::IsBusinessDay(const date &query_date) const {
  return !(IsHoliday(query_date) || IsWeekend(query_date));
}

bool BaseCalendar::IsHoliday(const date &query_date) const { return false; }

bool BaseCalendar::IsWeekend(const date &query_date) const {
  const auto day_of_week = query_date.day_of_week();
  return (day_of_week == boost::gregorian::Saturday ||
          day_of_week == boost::gregorian::Sunday);
}
}  // namespace qff_a
