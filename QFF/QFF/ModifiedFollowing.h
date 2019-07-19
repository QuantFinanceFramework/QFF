#pragma once
#include "Following.h"
#include "Preceding.h"

namespace qff {
	class ModifiedFollowing :
		public Following, public Preceding
	{
	public:
		date adjust(const date& originalDate, const ICalendar& calendar) const override;
	};
}
