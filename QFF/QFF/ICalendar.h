#pragma once
#include <boost\date_time\gregorian\gregorian.hpp>

namespace qff {
	using boost::gregorian::date;

	class ICalendar
	{
	public:
		ICalendar() = default;
		virtual ~ICalendar() = default;

		virtual bool isBusinessDay(const date& queryDate) const = 0;
		virtual bool isHoliday(const date& queryDate) const = 0;
		virtual bool isWeekend(const date& queryDate) const = 0;
	};
}
