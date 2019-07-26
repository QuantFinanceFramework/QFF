#pragma once
#include "BaseCalendar.h"

namespace qff {
class LondonCalendar : public BaseCalendar {
 public:
  unique_ptr<ICalendar> Clone() const override;
  bool IsHoliday(const date& query_date) const override;

 private:
  date EarlyMayBankHoliday(int year) const;
  static date SpringBankHoliday(int year);
  static date SummerBankHoliday(int year);
};
}  // namespace qff