#pragma once
#include "IDayCounter.h"

namespace qff {
class Actual365 : public IDayCounter {
 public:
  Actual365() = default;
  ~Actual365() = default;

  unique_ptr<IDayCounter> Clone() const override;

  double CalculateYearFraction(const date& start_date,
                               const date& end_date, const bool& is_maturity = false) const override;
};
}  // namespace qff
