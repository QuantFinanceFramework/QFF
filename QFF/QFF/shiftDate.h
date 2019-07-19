#pragma once
#include <boost\date_time\gregorian\gregorian.hpp>
#include "ICalendar.h"
#include "IBusinessDayConvention.h"

namespace qff {
	using boost::gregorian::date;

	enum class TimeUnit { d, w, m, y, b };

	date shiftDate(date originalDate, int length, TimeUnit timeUnit, const ICalendar& calendar, const IBusinessDayConvention& convention);

}