#pragma once
#include "IDayCounter.h"

namespace qff {
class Actual360 final : public IDayCounter {
 public:
  std::unique_ptr<IDayCounter> Clone() const override;

  double CalculateYearFraction(const boost::gregorian::date& start_date,
                               const boost::gregorian::date& end_date,
                               const bool& is_maturity = false) const override;
};
}  // namespace qff
