#pragma once
#include "BaseCalendar.h"

namespace qff {
class NewYorkCalendar : public BaseCalendar {
 public:
  unique_ptr<ICalendar> clone() override;
  bool isHoliday(const date& queryDate) const override;

  protected:
  date adjustHoliday(const date& holiday) const override;

 private:
  date martinLutherKingsBirthday(int year) const;
  date WashingtonsBirthday(int year) const;
  date memorialDay(int year) const;
  date independenceDay(int year) const;
  date labourDay(int year) const;
  date columbusDay(int year) const;
  date veteransDay(int year) const;
  date thanksgiveingDay(int year) const;
};
}  // namespace qff