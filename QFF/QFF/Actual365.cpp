#include "Actual365.h"

namespace qff {
unique_ptr<IDayCounter> Actual365::Clone() const {
  return std::make_unique<Actual365>();
}

double Actual365::CalculateYearFraction(const date& start_date,
                                        const date& end_date) const {
  const auto difference = end_date - start_date;
  return difference.days() / 365.0;
}
}  // namespace qff