#pragma once
#include "IDayCounter.h"

namespace qff {
class Actual360 : public IDayCounter {
 public:
  Actual360() = default;
  ~Actual360() = default;

  std::unique_ptr<IDayCounter> Clone() const override;

  double CalculateYearFraction(const boost::gregorian::date& start_date,
                               const boost::gregorian::date& end_date,
                               const bool& is_maturity = false) const override;
};
}  // namespace qff
