#include <CompositeCalendar.h>
#include <LondonCalendar.h>
#include <NewYorkCalendar.h>
#include <SydneyCalendar.h>
#include <boost\date_time\gregorian\gregorian.hpp>
#include <iostream>

using namespace qff;
using boost::gregorian::date;

int main() {
  SydneyCalendar syd{};
  NewYorkCalendar nyc{};
  LondonCalendar lon{};
  auto comp = CompositeCalendar(SydneyCalendar(), NewYorkCalendar(), LondonCalendar());
  date bankHoliday(2019, 8, 5);
  std::cout << "Bank Holiday is a holiday in Sydney: "
            << syd.isHoliday(bankHoliday) << '\n';
  std::cout << "Bank Holiday is a business day in Sydney: "
            << syd.isBusinessDay(bankHoliday) << '\n';
  std::cout << "Bank Holiday is a holiday in Composite Calendar: "
            << comp.isHoliday(bankHoliday) << '\n';
  std::cout << "Bank Holiday is a business day in Composite Calendar: "
            << comp.isBusinessDay(bankHoliday) << '\n';

  return 0;
}