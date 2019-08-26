#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include "IDayCounter.h"
#include "IBusinessDayConvention.h"
#include "ICalendar.h"
#include "Unadjusted.h"
#include "Period.h"

namespace qff {
double DateToTime(const IDayCounter& day_counter,
                  const boost::gregorian::date& start_date,
                  const boost::gregorian::date& end_date);

boost::gregorian::date ShiftDate(
    const boost::gregorian::date& original_date, const Period& period,
    const ICalendar& calendar,
    const IBusinessDayConvention& convention = Unadjusted());


}