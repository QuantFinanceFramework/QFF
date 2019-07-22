#pragma once
#include "IBusinessDayConvention.h"

namespace qff {
class ModifiedFollowing : public IBusinessDayConvention {
 public:
  unique_ptr<IBusinessDayConvention> clone() const override;

  date adjust(const date& originalDate,
              const ICalendar& calendar) const override;
};
}  // namespace qff
