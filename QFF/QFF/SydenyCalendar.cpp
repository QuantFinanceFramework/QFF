#include "SydneyCalendar.h"

using boost::gregorian::date;
using std::unique_ptr;

namespace qff {
using boost::date_time::next_weekday;

unique_ptr<ICalendar> SydneyCalendar::Clone() const {
  return std::make_unique<SydneyCalendar>();
}

bool SydneyCalendar::IsHoliday(const date& query_date) const {
  const auto year = query_date.year();
  return (
      (query_date == NewYearsDay(year)) || (query_date == AustraliaDay(year)) ||
      (query_date == GoodFriday(year)) || (query_date == EasterMonday(year)) ||
      (query_date == AnzacDay(year)) || (query_date == QueensBirthday(year)) ||
      (query_date == BankHoliday(year)) || (query_date == LabourDay(year)) ||
      (query_date == ChristmasDay(year)) || (query_date == BoxingDay(year)));
}

date SydneyCalendar::AustraliaDay(int year) const {
  return AdjustHoliday(date(year, 1, 26));
}

date SydneyCalendar::AnzacDay(int year) const {
  return AdjustHoliday(date(year, 4, 25));
}

date SydneyCalendar::QueensBirthday(int year) {
  return next_weekday(date(year, 6, 8),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date SydneyCalendar::BankHoliday(int year) {
  return next_weekday(date(year, 8, 1),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date SydneyCalendar::LabourDay(int year) {
  return next_weekday(date(year, 10, 1),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}
}  // namespace qff