#include "Actual365DayCounter.h"

namespace qff {
using std::make_unique;

unique_ptr<IDayCounter> Actual365DayCounter::clone() const {
  return make_unique<Actual365DayCounter>();
}

double Actual365DayCounter::countDayBetween(date startDate,
                                            date endDate) const {
  boost::gregorian::date_duration difference = endDate - startDate;

  return difference.days();
}

double Actual365DayCounter::calculateYearFraction(date startDate,
                                                  date endDate) const {
  return countDayBetween(startDate, endDate) / 365;
}
}  // namespace qff