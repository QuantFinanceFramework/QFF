#include "NewYorkCalendar.h"

namespace qff {
unique_ptr<ICalendar> NewYorkCalendar::clone() {
  return std::make_unique<NewYorkCalendar>();
}

bool NewYorkCalendar::isHoliday(const date& queryDate) const {
  auto year = queryDate.year();
  return (
      (queryDate == newYearsDay(year)) ||
      (queryDate == martinLutherKingsBirthday(year)) ||
      (queryDate == WashingtonsBirthday(year)) ||
      (queryDate == memorialDay(year)) ||
      (queryDate == independenceDay(year)) || (queryDate == labourDay(year)) ||
      (queryDate == columbusDay(year)) || (queryDate == veteransDay(year)) ||
      (queryDate == thanksgiveingDay(year)) ||
      (queryDate == christmasDay(year) || queryDate == newYearsDay(year + 1)));
}

date NewYorkCalendar::adjustHoliday(const date& holiday) const {
  auto w = holiday.day_of_week();
  if (w == boost::gregorian::Saturday)
    return holiday - boost::gregorian::days(1);
  if (w == boost::gregorian::Sunday) return holiday + boost::gregorian::days(1);
  return holiday;
}

date NewYorkCalendar::martinLutherKingsBirthday(int year) const {
  return next_weekday(date(year, 1, 15),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date NewYorkCalendar::WashingtonsBirthday(int year) const {
  return next_weekday(date(year, 2, 15),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date NewYorkCalendar::memorialDay(int year) const {
  return boost::date_time::previous_weekday(
      date(year, 5, 31),
      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date NewYorkCalendar::independenceDay(int year) const {
  return adjustHoliday(date(year, 7, 4));
}

date NewYorkCalendar::labourDay(int year) const {
  return next_weekday(date(year, 9, 1),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date NewYorkCalendar::columbusDay(int year) const {
  return next_weekday(date(year, 10, 8),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date NewYorkCalendar::veteransDay(int year) const {
  return adjustHoliday(date(year, 11, 11));
}

date NewYorkCalendar::thanksgiveingDay(int year) const {
  return next_weekday(date(year, 11, 22), boost::gregorian::greg_weekday(
                                              boost::date_time::Thursday));
}
}  // namespace qff