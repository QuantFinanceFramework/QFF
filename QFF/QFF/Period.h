#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include "IBusinessDayConvention.h"
#include "ICalendar.h"
#include "Unadjusted.h"

namespace qff {
using boost::gregorian::date;

enum class TimeUnit { d, w, m, y, b };

struct Period {
  Period() = default;
  Period(int length, TimeUnit unit);
  ~Period() = default;

  Period& operator+=(const Period& rhs);
  Period& operator-=(const Period& rhs);

  int length;
  TimeUnit unit;
};

Period operator+(const Period& lhs, const Period& rhs);

Period operator-(const Period& lhs, const Period& rhs);

date ShiftDate(const date& original_date, const Period& period,
               const ICalendar& calendar,
               const IBusinessDayConvention& convention = Unadjusted());

}  // namespace qff