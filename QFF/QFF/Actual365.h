#pragma once
#include "IDayCounter.h"

namespace qff {
class Actual365 : public IDayCounter {
 public:
  Actual365() = default;
  ~Actual365() = default;

  unique_ptr<IDayCounter> clone() const override;

  double calculateYearFraction(const date& startDate,
                               const date& endDate) const override;
};
}  // namespace qff
