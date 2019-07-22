#pragma once
#include <boost\date_time\gregorian\gregorian.hpp>
#include <memory>
#include "ICalendar.h"

namespace qff {
using boost::gregorian::date;
using std::unique_ptr;

class IBusinessDayConvention {
 public:
  IBusinessDayConvention() = default;
  virtual ~IBusinessDayConvention() = default;

  virtual unique_ptr<IBusinessDayConvention> clone() const = 0;

  virtual date adjust(const date& originalDate,
                      const ICalendar& calendar) const = 0;
};
}  // namespace qff
