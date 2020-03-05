#include "DateFunctions.h"
#include <memory>
#include "Following.h"
#include "Preceding.h"

using boost::gregorian::date;

namespace qff_a {
double DateToTime(const IDayCounter& day_counter, const date& start_date,
                  const date& end_date) {
  return day_counter.CalculateYearFraction(start_date, end_date);
}

date ShiftDate(const date& original_date, const Period& period,
               const ICalendar& calendar,
               const IBusinessDayConvention& convention) {
  switch (period.unit) {
    case TimeUnit::d:
      return convention.Adjust(
          original_date + boost::gregorian::days(period.length), calendar);
    case TimeUnit::w:
      return convention.Adjust(
          original_date + boost::gregorian::weeks(period.length), calendar);
    case TimeUnit::m:
      return convention.Adjust(
          original_date + boost::gregorian::months(period.length), calendar);
    case TimeUnit::y:
      return convention.Adjust(
          original_date + boost::gregorian::years(period.length), calendar);
    case TimeUnit::b:
      auto length = period.length;
      if (length > 0) {
        const auto following = std::make_unique<Following>();
        auto tmp_date = original_date;
        do {
          tmp_date =
              following->Adjust(tmp_date + boost::gregorian::days(1), calendar);
          length--;
        } while (length > 0);
        return tmp_date;
      }
      if (length < 0) {
        const auto preceding = std::make_unique<Preceding>();
        auto tmp_date = original_date;
        do {
          tmp_date =
              preceding->Adjust(tmp_date - boost::gregorian::days(1), calendar);
          length++;
        } while (length < 0);
        return tmp_date;
      }

      return original_date;
  }
  throw std::invalid_argument("invalid TimeUnit");
}
}  // namespace qff_a
