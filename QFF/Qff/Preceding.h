#pragma once
#include "IBusinessDayConvention.h"

namespace qff_a {
class Preceding final : public IBusinessDayConvention {
 public:
  std::unique_ptr<IBusinessDayConvention> Clone() const override;

  boost::gregorian::date Adjust(const boost::gregorian::date& original_date,
                                const ICalendar& calendar) const override;
};
}  // namespace qff_a
