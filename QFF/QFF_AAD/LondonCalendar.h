#pragma once
#include "BaseCalendar.h"

namespace qff_a {
class LondonCalendar final : public BaseCalendar {
 public:
  std::unique_ptr<ICalendar> Clone() const override;
  bool IsHoliday(const boost::gregorian::date& query_date) const override;

 private:
  boost::gregorian::date EarlyMayBankHoliday(int year) const;
  static boost::gregorian::date SpringBankHoliday(int year);
  static boost::gregorian::date SummerBankHoliday(int year);
};
}  // namespace qff