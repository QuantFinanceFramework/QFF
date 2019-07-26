#pragma once
#include "BaseCalendar.h"

namespace qff {
class SydneyCalendar : public BaseCalendar {
 public:
  unique_ptr<ICalendar> Clone() const override;
  bool IsHoliday(const date& query_date) const override;

 private:
  date AustraliaDay(int year) const;
  date AnzacDay(int year) const;
  static date QueensBirthday(int year);
  static date BankHoliday(int year);
  static date LabourDay(int year);
};
}  // namespace qff
