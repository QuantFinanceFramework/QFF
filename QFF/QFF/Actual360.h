#pragma once
#include "IDayCounter.h"

namespace qff {
class Actual360 : public IDayCounter {
 public:
  Actual360() = default;
  ~Actual360() = default;

  unique_ptr<IDayCounter> clone() const override;

  double calculateYearFraction(const date& startDate,
                               const date& endDate) const override;
};
}  // namespace qff
