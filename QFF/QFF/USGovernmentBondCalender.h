#pragma once
#include "BaseCalendar.h"

namespace qff {
	class USGovernmentBondCalender : public BaseCalendar
	{
	public:
		std::unique_ptr<ICalendar> Clone() const override;
		bool IsHoliday(const boost::gregorian::date& quary_date) const override;

	protected:
		boost::gregorian::date AdjustHoliday(
			const boost::gregorian::date& holiday) const override;
	private:
	};

} //namespace qff


