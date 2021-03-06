#include "SydneyCalendar.h"

using boost::gregorian::date;
using std::unique_ptr;

namespace qff_a {
using boost::date_time::next_weekday;

unique_ptr<ICalendar> SydneyCalendar::Clone() const {
  return std::make_unique<SydneyCalendar>(*this);
}

// A non business day is defined as any day on which banks in the
// state of NSW are generally obliged or permitted to close, including Saturday
// and Sunday. In general, AFMA recommends that transactions should not be
// negotiated for settlement or price fixing (rollover) on a non business day.
bool SydneyCalendar::IsHoliday(const date& query_date) const {
  const auto year = query_date.year();
  return (
      (query_date == NewYearsDay(year)) || (query_date == AustraliaDay(year)) ||
      (query_date == GoodFriday(year)) || (query_date == EasterMonday(year)) ||
      (query_date == AnzacDay(year)) || (query_date == QueensBirthday(year)) ||
      (query_date == BankHoliday(year)) || (query_date == LabourDay(year)) ||
      (query_date == ChristmasDay(year)) || (query_date == BoxingDay(year)));
}

date SydneyCalendar::AdjustHoliday(const date& holiday) const {
  const auto w = holiday.day_of_week();
  if (w == boost::gregorian::Saturday)
    return holiday + boost::gregorian::days(2);
  if (w == boost::gregorian::Sunday) return holiday + boost::gregorian::days(1);
  return holiday;
}

date SydneyCalendar::NewYearsDay(int year) const {
  return AdjustHoliday(date(year, 1, 1));
}

date SydneyCalendar::AustraliaDay(int year) const {
  return AdjustHoliday(date(year, 1, 26));
}

date SydneyCalendar::GoodFriday(int year) {
  return EasterMonday(year) - boost::gregorian::days(3);
}

date SydneyCalendar::EasterMonday(int year) {
  static constexpr int easter_monday_offset[] = {
      98,  90,  103, 95,  114, 106, 91,  111, 102,       // 1901-1909
      87,  107, 99,  83,  103, 95,  115, 99,  91,  111,  // 1910-1919
      96,  87,  107, 92,  112, 103, 95,  108, 100, 91,   // 1920-1929
      111, 96,  88,  107, 92,  112, 104, 88,  108, 100,  // 1930-1939
      85,  104, 96,  116, 101, 92,  112, 97,  89,  108,  // 1940-1949
      100, 85,  105, 96,  109, 101, 93,  112, 97,  89,   // 1950-1959
      109, 93,  113, 105, 90,  109, 101, 86,  106, 97,   // 1960-1969
      89,  102, 94,  113, 105, 90,  110, 101, 86,  106,  // 1970-1979
      98,  110, 102, 94,  114, 98,  90,  110, 95,  86,   // 1980-1989
      106, 91,  111, 102, 94,  107, 99,  90,  103, 95,   // 1990-1999
      115, 106, 91,  111, 103, 87,  107, 99,  84,  103,  // 2000-2009
      95,  115, 100, 91,  111, 96,  88,  107, 92,  112,  // 2010-2019
      104, 95,  108, 100, 92,  111, 96,  88,  108, 92,   // 2020-2029
      112, 104, 89,  108, 100, 85,  105, 96,  116, 101,  // 2030-2039
      93,  112, 97,  89,  109, 100, 85,  105, 97,  109,  // 2040-2049
      101, 93,  113, 97,  89,  109, 94,  113, 105, 90,   // 2050-2059
      110, 101, 86,  106, 98,  89,  102, 94,  114, 105,  // 2060-2069
      90,  110, 102, 86,  106, 98,  111, 102, 94,  114,  // 2070-2079
      99,  90,  110, 95,  87,  106, 91,  111, 103, 94,   // 2080-2089
      107, 99,  91,  103, 95,  115, 107, 91,  111, 103,  // 2090-2099
      88,  108, 100, 85,  105, 96,  109, 101, 93,  112,  // 2100-2109
      97,  89,  109, 93,  113, 105, 90,  109, 101, 86,   // 2110-2119
      106, 97,  89,  102, 94,  113, 105, 90,  110, 101,  // 2120-2129
      86,  106, 98,  110, 102, 94,  114, 98,  90,  110,  // 2130-2139
      95,  86,  106, 91,  111, 102, 94,  107, 99,  90,   // 2140-2149
      103, 95,  115, 106, 91,  111, 103, 87,  107, 99,   // 2150-2159
      84,  103, 95,  115, 100, 91,  111, 96,  88,  107,  // 2160-2169
      92,  112, 104, 95,  108, 100, 92,  111, 96,  88,   // 2170-2179
      108, 92,  112, 104, 89,  108, 100, 85,  105, 96,   // 2180-2189
      116, 101, 93,  112, 97,  89,  109, 100, 85,  105   // 2190-2199
  };
  return date(year - 1, 12, 31) +
         boost::gregorian::days(easter_monday_offset[year - 1901]);
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

date SydneyCalendar::ChristmasDay(int year) const {
  return AdjustHoliday(date(year, 12, 25));
}

date SydneyCalendar::BoxingDay(int year) const {
  const auto boxing_day = date(year, 12, 26);
  const auto day_of_week = boxing_day.day_of_week();
  if (day_of_week == boost::gregorian::Saturday)
    return boxing_day + boost::gregorian::days(2);
  if (day_of_week == boost::gregorian::Sunday)
    return boxing_day + boost::gregorian::days(2);
  return AdjustHoliday(boxing_day);
}
}  // namespace qff_a