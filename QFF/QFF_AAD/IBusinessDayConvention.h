#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <memory>
#include "ICalendar.h"

namespace qff_a {
class IBusinessDayConvention {
 public:
  virtual ~IBusinessDayConvention() = default;

  virtual std::unique_ptr<IBusinessDayConvention> Clone() const = 0;

  virtual boost::gregorian::date Adjust(
      const boost::gregorian::date& original_date,
      const ICalendar& calendar) const = 0;
};
}  // namespace qff_a
