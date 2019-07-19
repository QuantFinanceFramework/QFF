#include "AustraliaCalendar.h"

namespace qff {
using boost::date_time::next_weekday;

bool AustraliaCalendar::isHoliday(const date& queryDate) const {
  auto year = queryDate.year();
  return (isWeekend(queryDate) || (queryDate == newYearsDay(year)) ||
          (queryDate == australiaDay(year)) ||
          (queryDate == goodFriday(year)) ||
          (queryDate == easterMonday(year)) || (queryDate == anzacDay(year)) ||
          (queryDate == queensBirthday(year)) ||
          (queryDate == bankHoliday(year)) || (queryDate == labourDay(year)) ||
          (queryDate == christmasDay(year)) || (queryDate == boxingDay(year)));
}

date AustraliaCalendar::australiaDay(int year) const {
  return adjustHoliday(date(year, 1, 26));
}

date AustraliaCalendar::anzacDay(int year) const {
  return adjustHoliday(date(year, 4, 25));
}

date AustraliaCalendar::queensBirthday(int year) const {
  return next_weekday(date(year, 6, 8),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date AustraliaCalendar::bankHoliday(int year) const {
  return next_weekday(date(year, 8, 1),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date AustraliaCalendar::labourDay(int year) const {
  return next_weekday(date(year, 10, 1),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}
}  // namespace qff