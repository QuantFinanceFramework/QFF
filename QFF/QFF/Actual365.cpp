#include "Actual365.h"

using boost::gregorian::date;
using std::unique_ptr;

namespace qff {
unique_ptr<IDayCounter> Actual365::Clone() const {
  return std::make_unique<Actual365>(*this);
}

double Actual365::CalculateYearFraction(const date& start_date,
                                        const date& end_date,
                                        const bool& is_maturity) const {
  const auto difference = end_date - start_date;
  return difference.days() / 365.0;
}
}  // namespace qff