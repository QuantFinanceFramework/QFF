#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <memory>

namespace qff {
using boost::gregorian::date;
using std::unique_ptr;

class ICalendar {
 public:
  ICalendar() = default;
  virtual ~ICalendar() = default;

  virtual unique_ptr<ICalendar> Clone() const = 0;

  virtual bool IsBusinessDay(const date& query_date) const = 0;
  virtual bool IsHoliday(const date& query_date) const = 0;
  virtual bool IsWeekend(const date& query_date) const = 0;
};
}  // namespace qff
