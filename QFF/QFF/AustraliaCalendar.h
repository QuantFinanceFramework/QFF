#pragma once
#include "BaseCalendar.h"

namespace qff {
	class AustraliaCalendar :
		public BaseCalendar
	{
	public:
		bool isHoliday(const date& queryDate) const override;

	private:
		date australiaDay(int year) const;
		date anzacDay(int year) const;
		date queensBirthday(int year) const;
		date bankHoliday(int year) const;
		date labourDay(int year) const;
	};
}
