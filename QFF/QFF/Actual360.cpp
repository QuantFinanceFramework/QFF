#include "Actual360.h"

namespace qff {
unique_ptr<IDayCounter> Actual360::clone() const {
  return std::make_unique<Actual360>();
}

double Actual360::calculateYearFraction(const date& startDate,
                                        const date& endDate) const {
  auto difference = endDate - startDate;
  return difference.days() / 360.0;
}
}  // namespace qff