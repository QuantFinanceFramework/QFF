#include "AustraliaCalendar.h"

namespace qff {
	using boost::date_time::next_weekday;
	using boost::date_time::Monday;

	bool qff::AustraliaCalendar::isHoliday(const date& queryDate) const
	{
		auto year = queryDate.year();
		return (isWeekend(queryDate)
			|| (queryDate == newYearsDay(year))
			|| (queryDate == australiaDay(year))
			|| (queryDate == goodFriday(year))
			|| (queryDate == easterMonday(year))
			|| (queryDate == anzacDay(year))
			|| (queryDate == queensBirthday(year))
			|| (queryDate == bankHoliday(year))
			|| (queryDate == labourDay(year))
			|| (queryDate == christmasDay(year))
			|| (queryDate == boxingDay(year)));
	}

	date AustraliaCalendar::australiaDay(int year) const
	{
		return adjustHoliday(date(year, 1, 26));
	}

	date AustraliaCalendar::anzacDay(int year) const
	{
		return adjustHoliday(date(year, 4, 25));
	}

	date AustraliaCalendar::queensBirthday(int year) const
	{
		return next_weekday(next_weekday(date(year, 6, 1), Monday), Monday);
	}

	date AustraliaCalendar::bankHoliday(int year) const
	{
		return next_weekday(date(year, 8, 1), Monday);
	}

	date AustraliaCalendar::labourDay(int year) const
	{
		return next_weekday(date(year, 10, 1), Monday);
	}
}