#include "SydneyCalendar.h"

namespace qff {
using boost::date_time::next_weekday;

unique_ptr<ICalendar> SydneyCalendar::clone() const {
  return std::make_unique<SydneyCalendar>();
}

bool SydneyCalendar::isHoliday(const date& queryDate) const {
  auto year = queryDate.year();
  return (
      (queryDate == newYearsDay(year)) || (queryDate == australiaDay(year)) ||
      (queryDate == goodFriday(year)) || (queryDate == easterMonday(year)) ||
      (queryDate == anzacDay(year)) || (queryDate == queensBirthday(year)) ||
      (queryDate == bankHoliday(year)) || (queryDate == labourDay(year)) ||
      (queryDate == christmasDay(year)) || (queryDate == boxingDay(year)));
}

date SydneyCalendar::australiaDay(int year) const {
  return adjustHoliday(date(year, 1, 26));
}

date SydneyCalendar::anzacDay(int year) const {
  return adjustHoliday(date(year, 4, 25));
}

date SydneyCalendar::queensBirthday(int year) const {
  return next_weekday(date(year, 6, 8),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date SydneyCalendar::bankHoliday(int year) const {
  return next_weekday(date(year, 8, 1),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date SydneyCalendar::labourDay(int year) const {
  return next_weekday(date(year, 10, 1),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}
}  // namespace qff