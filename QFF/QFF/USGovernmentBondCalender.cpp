#include "USGovernmentBondCalender.h"

using boost::gregorian::date;
using std::unique_ptr;

namespace qff {
	unique_ptr<ICalendar> USGovernmentBondCalender::Clone() const {
		return std::make_unique<USGovernmentBondCalender>();
	}

	bool USGovernmentBondCalender::IsHoliday(const date& query_date) const {
		const auto year = query_date.year();
		return ((query_date == NewYearsDay(year)) ||
			(query_date == MartinLutherKingsBirthday(year)) ||
			(query_date == WashingtonsBirthday(year)) ||
			(query_date == MemorialDay(year)) ||
			(query_date == IndependenceDay(year)) ||
			(query_date == LabourDay(year)) ||
			(query_date == ColumbusDay(year)) ||
			(query_date == VeteransDay(year)) ||
			(query_date == ThanksgivingDay(year)) ||
			(query_date == ChristmasDay(year) || 
				query_date == NewYearsDay(year + 1)) ||
			(query_date == GoodFriday(year)));
	}

	date USGovernmentBondCalender::AdjustHoliday(const date& holiday) const {
		const auto w = holiday.day_of_week();
		if (w == boost::gregorian::Saturday)
			return holiday - boost::gregorian::days(1);
		if (w == boost::gregorian::Sunday) return holiday + boost::gregorian::days(1);
		return holiday;
	}

	date USGovernmentBondCalender::MartinLutherKingsBirthday(int year) const {
		return next_weekday(date(year, 1, 15),
			boost::gregorian::greg_weekday(boost::date_time::Monday));
	}

	date USGovernmentBondCalender::WashingtonsBirthday(int year) const {
		return next_weekday(date(year, 2, 15),
			boost::gregorian::greg_weekday(boost::date_time::Monday));
	}

	date USGovernmentBondCalender::MemorialDay(int year) {
		return boost::date_time::previous_weekday(
			date(year, 5, 31),
			boost::gregorian::greg_weekday(boost::date_time::Monday));
	}

	date USGovernmentBondCalender::IndependenceDay(int year) const {
		return AdjustHoliday(date(year, 7, 4));
	}

	date USGovernmentBondCalender::LabourDay(int year) const {
		return next_weekday(date(year, 9, 1),
			boost::gregorian::greg_weekday(boost::date_time::Monday));
	}

	date USGovernmentBondCalender::ColumbusDay(int year) const {
		return next_weekday(date(year, 10, 8),
			boost::gregorian::greg_weekday(boost::date_time::Monday));
	}

	date USGovernmentBondCalender::VeteransDay(int year) const {
		return AdjustHoliday(date(year, 11, 11));
	}

	date USGovernmentBondCalender::ThanksgivingDay(int year) const {
		return next_weekday(date(year, 11, 22), boost::gregorian::greg_weekday(
			boost::date_time::Thursday));
	}	

}  // namespace qff