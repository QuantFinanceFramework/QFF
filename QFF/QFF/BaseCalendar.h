#pragma once
#include "ICalendar.h"

namespace qff {
class BaseCalendar : public ICalendar {
 public:
  BaseCalendar() = default;
  ~BaseCalendar() = default;

  unique_ptr<ICalendar> Clone() const override;

  bool IsBusinessDay(const date& query_date) const final;
  bool IsHoliday(const date& query_date) const override;
  bool IsWeekend(const date& query_date) const final;

 protected:
  virtual date AdjustHoliday(const date& holiday) const;
  date NewYearsDay(int year) const;
  static date EasterMonday(int year);
  static date GoodFriday(int year);
  date ChristmasDay(int year) const;
  date BoxingDay(int year) const;
};
}  // namespace qff
