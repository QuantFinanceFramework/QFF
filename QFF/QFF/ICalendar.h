#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <memory>

namespace qff {
class ICalendar {
 public:
  virtual ~ICalendar() = default;

  virtual std::unique_ptr<ICalendar> Clone() const = 0;

  virtual bool IsBusinessDay(
      const boost::gregorian::date& query_date) const = 0;
  virtual bool IsHoliday(const boost::gregorian::date& query_date) const = 0;
  virtual bool IsWeekend(const boost::gregorian::date& query_date) const = 0;
};
}  // namespace qff
