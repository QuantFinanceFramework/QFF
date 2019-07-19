#pragma once
#include "IBusinessDayConvention.h"

namespace qff {
class Following : public IBusinessDayConvention {
 public:
  date adjust(const date& originalDate,
              const ICalendar& calendar) const override;
};
}  // namespace qff