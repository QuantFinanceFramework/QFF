#include "Following.h"

using boost::gregorian::date;
using std::unique_ptr;

namespace qff_a {
unique_ptr<IBusinessDayConvention> Following::Clone() const {
  return std::make_unique<Following>(*this);
}

date Following::Adjust(const date& original_date,
                       const ICalendar& calendar) const {
  if (calendar.IsBusinessDay(original_date)) return original_date;
  auto tmp_date = original_date;
  do {
    tmp_date += boost::gregorian::days(1);
  } while (!calendar.IsBusinessDay(tmp_date));
  return tmp_date;
}
}  // namespace qff