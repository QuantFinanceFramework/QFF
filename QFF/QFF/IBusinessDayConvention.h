#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <memory>
#include "ICalendar.h"

namespace qff {
using boost::gregorian::date;
using std::unique_ptr;

class IBusinessDayConvention {
 public:
  IBusinessDayConvention() = default;
  virtual ~IBusinessDayConvention() = default;

  virtual unique_ptr<IBusinessDayConvention> Clone() const = 0;

  virtual date Adjust(const date& original_date,
                      const ICalendar& calendar) const = 0;
};
}  // namespace qff
