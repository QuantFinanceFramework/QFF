#include "UsBondMarketCalendar.h"

using boost::gregorian::date;
using std::unique_ptr;

namespace qff_a {
unique_ptr<ICalendar> UsBondMarketCalendar::Clone() const {
  return std::make_unique<UsBondMarketCalendar>(*this);
}

bool UsBondMarketCalendar::IsHoliday(const date& query_date) const {
  const auto year = query_date.year();
  return (
      (query_date == NewYearsDay(year)) ||
      (query_date == MartinLutherKingsBirthday(year)) ||
      (query_date == WashingtonsBirthday(year)) ||
      (query_date == GoodFriday(year)) || (query_date == MemorialDay(year)) ||
      (query_date == IndependenceDay(year)) ||
      (query_date == LabourDay(year)) || (query_date == ColumbusDay(year)) ||
      (query_date == VeteransDay(year)) ||
      (query_date == ThanksgivingDay(year)) ||
      (query_date == ChristmasDay(year)));
}

// If a holiday falls on a Sunday, exchanges are closed on Monday. If a holiday
// falls on Saturday, exchanges are closed on the preceding Friday UNLESS
// unusual business conditions exist, such as the ending of a monthly or yearly
// accounting period.
date UsBondMarketCalendar::AdjustHoliday(const date& holiday) const {
  const auto w = holiday.day_of_week();
  if (w == boost::gregorian::Saturday)
    return holiday - boost::gregorian::days(1);
  if (w == boost::gregorian::Sunday) return holiday + boost::gregorian::days(1);
  return holiday;
}

// If New Year's Day falls on a Saturday, no adjustment will be applied
// As 31 December is the end of an accounting period, the exchange remains open.
date UsBondMarketCalendar::NewYearsDay(int year) {
  date nyd(year, 1, 1);
  const auto w = nyd.day_of_week();
  if (nyd.day_of_week() == boost::gregorian::Sunday) return date(year, 1, 2);
  return nyd;
}

date UsBondMarketCalendar::MartinLutherKingsBirthday(int year) const {
  return next_weekday(date(year, 1, 15),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date UsBondMarketCalendar::WashingtonsBirthday(int year) const {
  return next_weekday(date(year, 2, 15),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date UsBondMarketCalendar::GoodFriday(int year) {
  return EasterMonday(year) - boost::gregorian::days(3);
}

// Easter Monday is NOT a US bond market holiday
// This is used for Good Friday calculation only.
date UsBondMarketCalendar::EasterMonday(int year) {
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

date UsBondMarketCalendar::MemorialDay(int year) {
  return boost::date_time::previous_weekday(
      date(year, 5, 31),
      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date UsBondMarketCalendar::IndependenceDay(int year) const {
  return AdjustHoliday(date(year, 7, 4));
}

date UsBondMarketCalendar::LabourDay(int year) const {
  return next_weekday(date(year, 9, 1),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date UsBondMarketCalendar::ColumbusDay(int year) const {
  return next_weekday(date(year, 10, 8),
                      boost::gregorian::greg_weekday(boost::date_time::Monday));
}

date UsBondMarketCalendar::VeteransDay(int year) const {
  return AdjustHoliday(date(year, 11, 11));
}

date UsBondMarketCalendar::ThanksgivingDay(int year) const {
  return next_weekday(date(year, 11, 22), boost::gregorian::greg_weekday(
                                              boost::date_time::Thursday));
}

date UsBondMarketCalendar::ChristmasDay(int year) const {
  return AdjustHoliday(date(year, 12, 25));
}
}  // namespace qff_a