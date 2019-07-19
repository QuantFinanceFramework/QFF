#pragma once
#include <boost\date_time\gregorian\gregorian.hpp>
#include "ICalendar.h"

namespace qff {
using boost::gregorian::date;

class IBusinessDayConvention {
 public:
  virtual date adjust(const date& originalDate,
                      const ICalendar& calendar) const = 0;
};
}  // namespace qff