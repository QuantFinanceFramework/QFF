#pragma once
#include "IBusinessDayConvention.h"

namespace qff {
class ModifiedFollowing : public IBusinessDayConvention {
 public:
  unique_ptr<IBusinessDayConvention> Clone() const override;

  date Adjust(const date& original_date,
              const ICalendar& calendar) const override;
};
}  // namespace qff
