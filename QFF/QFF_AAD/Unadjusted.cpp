#include "Unadjusted.h"

using boost::gregorian::date;
using std::unique_ptr;

namespace qff_a {
unique_ptr<IBusinessDayConvention> Unadjusted::Clone() const {
  return std::make_unique<Unadjusted>(*this);
}

date Unadjusted::Adjust(const date& original_date,
                        const ICalendar& calendar) const {
  return original_date;
}
}  // namespace qff_a