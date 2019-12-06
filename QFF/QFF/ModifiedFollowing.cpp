#include "ModifiedFollowing.h"
#include "Following.h"
#include "Preceding.h"

using boost::gregorian::date;
using std::unique_ptr;

namespace qff {
unique_ptr<IBusinessDayConvention> ModifiedFollowing::Clone() const {
  return std::make_unique<ModifiedFollowing>(*this);
}

date ModifiedFollowing::Adjust(const date& original_date,
                               const ICalendar& calendar) const {
  const auto following = std::make_unique<Following>();
  const auto tmp_date = following->Adjust(original_date, calendar);
  if (tmp_date.month() == original_date.month()) return tmp_date;
  const auto preceding = std::make_unique<Preceding>();
  return preceding->Adjust(original_date, calendar);
}
}  // namespace qff