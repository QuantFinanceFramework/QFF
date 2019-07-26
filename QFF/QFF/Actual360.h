#pragma once
#include "IDayCounter.h"

namespace qff {
class Actual360 : public IDayCounter {
 public:
  Actual360() = default;
  ~Actual360() = default;

  unique_ptr<IDayCounter> Clone() const override;

  double CalculateYearFraction(const date& start_date,
                               const date& end_date) const override;
};
}  // namespace qff
