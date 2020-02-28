#include "SydneyCalendar.h"

using boost::gregorian::date;
using std::unique_ptr;

namespace qff_a {
using boost::date_time::next_weekday;

unique_ptr<ICalendar> SydneyCalendar::Clone() const {
  return std::make_unique<SydneyCalendar>(*this);
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

// ANZAC day is not adjusted in NSW.
date SydneyCalendar::AnzacDay(int year) { return date(year, 4, 25); }

// Queen's Birthday public holiday on the second Monday in June.
date SydneyCalendar::QueensBirthday(int year) {
  return next_weekday(date(year, 6, 8),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

// NSW Bank Holiday on the first Monday in August.
date SydneyCalendar::BankHoliday(int year) {
  return next_weekday(date(year, 8, 1),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

// Labour Day public holiday on the first Monday in October.
date SydneyCalendar::LabourDay(int year) {
  return next_weekday(date(year, 10, 1),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}
}  // namespace qff_a