#pragma once
#include "ICalendar.h"

namespace qff {
class BaseCalendar : public ICalendar {
 public:
  BaseCalendar() = default;
  ~BaseCalendar() = default;

  bool isBusinessDay(const date& queryDate) const final;
  bool isWeekend(const date& queryDate) const final;

 protected:
  date adjustHoliday(const date& holiday) const;
  date newYearsDay(int year) const;
  date easterMonday(int year) const;
  date goodFriday(int year) const;
  date christmasDay(int year) const;
  date boxingDay(int year) const;
};
}  // namespace qff
