#pragma once
#include "ICalendar.h"

namespace qff {
class BaseCalendar : public ICalendar {
 public:
  BaseCalendar() = default;
  ~BaseCalendar() = default;

  std::unique_ptr<ICalendar> Clone() const override;

  bool IsBusinessDay(const boost::gregorian::date& query_date) const final;
  bool IsHoliday(const boost::gregorian::date& query_date) const override;
  bool IsWeekend(const boost::gregorian::date& query_date) const final;

 protected:
  virtual boost::gregorian::date AdjustHoliday(
      const boost::gregorian::date& holiday) const;
  boost::gregorian::date NewYearsDay(int year) const;
  static boost::gregorian::date EasterMonday(int year);
  static boost::gregorian::date GoodFriday(int year);
  boost::gregorian::date ChristmasDay(int year) const;
  boost::gregorian::date BoxingDay(int year) const;
};
}  // namespace qff
