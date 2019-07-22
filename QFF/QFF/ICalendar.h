#pragma once
#include <boost\date_time\gregorian\gregorian.hpp>
#include <memory>

namespace qff {
using boost::gregorian::date;
using std::unique_ptr;

class ICalendar {
 public:
  ICalendar() = default;
  virtual ~ICalendar() = default;

  virtual unique_ptr<ICalendar> clone() const = 0;

  virtual bool isBusinessDay(const date& queryDate) const = 0;
  virtual bool isHoliday(const date& queryDate) const = 0;
  virtual bool isWeekend(const date& queryDate) const = 0;
};
}  // namespace qff
