#include <CompositeCalendar.h>
#include <LondonCalendar.h>
#include <NewYorkCalendar.h>
#include <SydneyCalendar.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>

using namespace qff;
using boost::gregorian::date;

int main() {
  const SydneyCalendar syd{};
  const auto comp =
      CompositeCalendar(SydneyCalendar(), NewYorkCalendar(), LondonCalendar());
  const auto comp2 = comp.Clone();

  const date bank_holiday(2019, 8, 5);
  std::cout << "Bank Holiday is a holiday in Sydney: "
            << syd.IsHoliday(bank_holiday) << '\n';
  std::cout << "Bank Holiday is a business day in Sydney: "
            << syd.IsBusinessDay(bank_holiday) << '\n';
  std::cout << "Bank Holiday is a holiday in Composite Calendar: "
            << comp.IsHoliday(bank_holiday) << '\n';
  std::cout << "Bank Holiday is a business day in Composite Calendar: "
            << comp.IsBusinessDay(bank_holiday) << '\n';
  std::cout << "Bank Holiday is a holiday in Composite Calendar (Clone): "
            << comp2->IsHoliday(bank_holiday) << '\n';
  std::cout << "Bank Holiday is a business day in Composite Calendar (Clone): "
            << comp2->IsBusinessDay(bank_holiday) << '\n';
  return 0;
}