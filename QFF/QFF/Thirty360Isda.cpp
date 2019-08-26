#include "Thirty360Isda.h"

using boost::gregorian::date;
using std::unique_ptr;

namespace qff {
unique_ptr<IDayCounter> Thirty360Isda::Clone() const {
  return std::make_unique<Thirty360Isda>();
}

double Thirty360Isda::CalculateYearFraction(const date& start_date,
                                            const date& end_date,
                                            const bool& is_maturity) const {
  int y1 = start_date.year();
  int y2 = end_date.year();
  int m1 = start_date.month();
  int m2 = end_date.month();
  int d1 = start_date.day();
  int d2 = end_date.day();

  if (d1 == 31 || d1 == date(y1, 2, 28).end_of_month().day()) d1 = 30;

  if (d2 == 31 || (d2 == date(y2, 2, 28).end_of_month().day() && !is_maturity))
    d2 = 30;

  return (360.0 * (y2 - y1) + 30.0 * (m2 - m1) + (d2 - d1)) / 360.0;
}

}  // namespace qff