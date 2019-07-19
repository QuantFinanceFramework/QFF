#include "shiftDate.h"

namespace qff {
	date shiftDate(date originalDate, int length, TimeUnit timeUnit, const ICalendar& calendar, const IBusinessDayConvention& convention)
	{
		switch (timeUnit)
		{
		case TimeUnit::d: 
			return convention.adjust(originalDate + boost::gregorian::days(length), calendar);
		case TimeUnit::w: 
			return convention.adjust(originalDate + boost::gregorian::weeks(length), calendar);
		case TimeUnit::m: 
			return convention.adjust(originalDate + boost::gregorian::months(length), calendar);
		case TimeUnit::y: 
			return convention.adjust(originalDate + boost::gregorian::years(length), calendar);
		case TimeUnit::b: 
			throw "myFunction is not implemented yet.";
		}
	}
}