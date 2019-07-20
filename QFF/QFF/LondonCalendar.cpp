#include "LondonCalendar.h"

namespace qff {
bool LondonCalendar::isHoliday(const date& queryDate) const {
  auto year = queryDate.year();
  return ((queryDate == newYearsDay(year)) || (queryDate == goodFriday(year)) ||
          (queryDate == easterMonday(year)) ||
          (queryDate == earlyMayBankHoliday(year)) ||
          (queryDate == springBankHoliday(year)) ||
          (queryDate == summerBankHoliday(year)) ||
          (queryDate == christmasDay(year)) || (queryDate == boxingDay(year)));
}

date LondonCalendar::earlyMayBankHoliday(int year) const {
  // In 2020, Early May Bank Holiday moves to 8th May to coincide with VE Day
  if (year == 2020) return date(2020, 5, 8);
  return next_weekday(date(year, 5, 1),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date LondonCalendar::springBankHoliday(int year) const {
  return boost::date_time::previous_weekday(
      date(year, 5, 31),
      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date LondonCalendar::summerBankHoliday(int year) const {
  return boost::date_time::previous_weekday(
      date(year, 8, 31),
      boost::gregorian::greg_weekday(boost::date_time::Monday));
}
}  // namespace qff