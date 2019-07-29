#include "Actual360.h"

namespace qff {
unique_ptr<IDayCounter> Actual360::Clone() const {
  return std::make_unique<Actual360>();
}

double Actual360::CalculateYearFraction(const date& start_date,
                                        const date& end_date,
                                        const bool& is_maturity) const {
  const auto difference = end_date - start_date;
  return difference.days() / 360.0;
}
}  // namespace qff