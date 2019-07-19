#pragma once
#include "IDayCounter.h"

namespace qff {
class Actual365DayCounter : public IDayCounter {
 public:
  Actual365DayCounter() = default;
  ~Actual365DayCounter() = default;

  unique_ptr<IDayCounter> clone() const override;

  double countDayBetween(date startDate, date endDate) const override;
  double calculateYearFraction(date startDate, date endDate) const override;
};
}  // namespace qff
