#include "Actual365.h"

namespace qff {
unique_ptr<IDayCounter> Actual365::clone() const {
  return std::make_unique<Actual365>();
}

double Actual365::calculateYearFraction(const date& startDate,
                                        const date& endDate) const {
  auto difference = endDate - startDate;
  return difference.days() / 365.0;
}
}  // namespace qff