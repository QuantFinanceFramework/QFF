#pragma once
#include <boost\date_time\gregorian\gregorian.hpp>

namespace qff {
	using boost::gregorian::date;

	class ICalendar
	{
	public:
		ICalendar() = default;
		virtual ~ICalendar() = default;

		virtual bool isHoliday(date queryDate) const = 0;
		virtual bool isBusinessDay(date queryDate) const = 0;
	};
}
