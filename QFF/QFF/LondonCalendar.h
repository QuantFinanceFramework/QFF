#pragma once
#include "BaseCalendar.h"

namespace qff {
class LondonCalendar : public BaseCalendar {
 public:
  unique_ptr<ICalendar> clone() const override;
  bool isHoliday(const date& queryDate) const override;

 private:
  date earlyMayBankHoliday(int year) const;
  date springBankHoliday(int year) const;
  date summerBankHoliday(int year) const;
};
}  // namespace qff