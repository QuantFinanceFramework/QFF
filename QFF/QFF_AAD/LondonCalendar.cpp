#include "LondonCalendar.h"

using boost::gregorian::date;
using std::unique_ptr;

namespace qff_a {
unique_ptr<ICalendar> LondonCalendar::Clone() const {
  return std::make_unique<LondonCalendar>(*this);
}

bool LondonCalendar::IsHoliday(const date& query_date) const {
  const auto year = query_date.year();
  return (
      (query_date == NewYearsDay(year)) || (query_date == GoodFriday(year)) ||
      (query_date == EasterMonday(year)) ||
      (query_date == EarlyMayBankHoliday(year)) ||
      (query_date == SpringBankHoliday(year)) ||
      (query_date == SummerBankHoliday(year)) ||
      (query_date == ChristmasDay(year)) || (query_date == BoxingDay(year)));
}

date LondonCalendar::EarlyMayBankHoliday(int year) const {
  // In 2020, Early May Bank Holiday moves to 8th May to coincide with VE Day
  if (year == 2020) return date(2020, 5, 8);
  return next_weekday(date(year, 5, 1),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date LondonCalendar::SpringBankHoliday(int year) {
  return boost::date_time::previous_weekday(
      date(year, 5, 31),
      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date LondonCalendar::SummerBankHoliday(int year) {
  return boost::date_time::previous_weekday(
      date(year, 8, 31),
      boost::gregorian::greg_weekday(boost::date_time::Monday));
}
}  // namespace qff_a