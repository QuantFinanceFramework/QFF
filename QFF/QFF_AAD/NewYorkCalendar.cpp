#include "NewYorkCalendar.h"

using boost::gregorian::date;
using std::unique_ptr;

namespace qff_a {
unique_ptr<ICalendar> NewYorkCalendar::Clone() const {
  return std::make_unique<NewYorkCalendar>(*this);
}

// Federal Reserve Bank of New York offices are closed on Saturdays and Sundays
// and the following holiday observances: New Year's Day,
// Birthday Of Martin Luther King, Washington's Birthday, Memorial Day,
// Independence Day, Labor Day, Columbus Day, Veterans Day, Thanksgiving Day,
// and Christmas Day.
bool NewYorkCalendar::IsHoliday(const date& query_date) const {
  const auto year = query_date.year();
  return ((query_date == NewYearsDay(year)) ||
          (query_date == MartinLutherKingsBirthday(year)) ||
          (query_date == WashingtonsBirthday(year)) ||
          (query_date == MemorialDay(year)) ||
          (query_date == IndependenceDay(year)) ||
          (query_date == LabourDay(year)) ||
          (query_date == ColumbusDay(year)) ||
          (query_date == VeteransDay(year)) ||
          (query_date == ThanksgivingDay(year)) ||
          (query_date == ChristmasDay(year)));
}

// For holidays falling on Sunday, the New York Fed will be closed the following
// Monday.
date NewYorkCalendar::AdjustHoliday(const date& holiday) const {
  const auto w = holiday.day_of_week();
  if (w == boost::gregorian::Sunday) return holiday + boost::gregorian::days(1);
  return holiday;
}

date NewYorkCalendar::NewYearsDay(int year) const {
  return AdjustHoliday(date(year, 1, 1));
}

date NewYorkCalendar::MartinLutherKingsBirthday(int year) const {
  return next_weekday(date(year, 1, 15),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date NewYorkCalendar::WashingtonsBirthday(int year) const {
  return next_weekday(date(year, 2, 15),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date NewYorkCalendar::MemorialDay(int year) {
  return boost::date_time::previous_weekday(
      date(year, 5, 31),
      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date NewYorkCalendar::IndependenceDay(int year) const {
  return AdjustHoliday(date(year, 7, 4));
}

date NewYorkCalendar::LabourDay(int year) const {
  return next_weekday(date(year, 9, 1),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date NewYorkCalendar::ColumbusDay(int year) const {
  return next_weekday(date(year, 10, 8),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date NewYorkCalendar::VeteransDay(int year) const {
  return AdjustHoliday(date(year, 11, 11));
}

date NewYorkCalendar::ThanksgivingDay(int year) const {
  return next_weekday(date(year, 11, 22), boost::gregorian::greg_weekday(
                                              boost::date_time::Thursday));
}

date NewYorkCalendar::ChristmasDay(int year) const {
  return AdjustHoliday(date(year, 12, 25));
}
}  // namespace qff_a