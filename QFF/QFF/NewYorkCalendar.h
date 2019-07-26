#pragma once
#include "BaseCalendar.h"

namespace qff {
class NewYorkCalendar : public BaseCalendar {
 public:
  unique_ptr<ICalendar> Clone() const override;
  bool IsHoliday(const date& query_date) const override;

  protected:
  date AdjustHoliday(const date& holiday) const override;

 private:
  date MartinLutherKingsBirthday(int year) const;
  date WashingtonsBirthday(int year) const;
  static date MemorialDay(int year);
  date IndependenceDay(int year) const;
  date LabourDay(int year) const;
  date ColumbusDay(int year) const;
  date VeteransDay(int year) const;
  date ThanksgivingDay(int year) const;
};
}  // namespace qff