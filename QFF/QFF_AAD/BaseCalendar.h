#pragma once
#include "ICalendar.h"

namespace qff_a {
class BaseCalendar : public ICalendar {
 public:
  std::unique_ptr<ICalendar> Clone() const override;

  bool IsBusinessDay(
      const boost::gregorian::date& query_date) const override final;
  bool IsHoliday(const boost::gregorian::date& query_date) const override;
  bool IsWeekend(const boost::gregorian::date& query_date) const override final;
};
}  // namespace qff_a
