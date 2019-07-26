#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include "IBusinessDayConvention.h"
#include "ICalendar.h"
#include "Unadjusted.h"

namespace qff {
using boost::gregorian::date;

enum class TimeUnit { d, w, m, y, b };

struct Period {
  int length;
  TimeUnit unit;
};

date ShiftDate(const date& original_date, const Period& period,
               const ICalendar& calendar,
               const IBusinessDayConvention& convention = Unadjusted());

}  // namespace qff