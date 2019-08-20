#include "DateFunctions.h"

namespace qff {
double DateToTime(const IDayCounter& day_counter, const date& start_date,
                  const date& end_date) {
  return day_counter.CalculateYearFraction(start_date, end_date);
}
}  // namespace qff
