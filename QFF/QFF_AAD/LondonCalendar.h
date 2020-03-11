#pragma once
#include "BaseCalendar.h"

namespace qff_a {
class LondonCalendar final : public BaseCalendar {
 public:
  std::unique_ptr<ICalendar> Clone() const override;
  bool IsHoliday(const boost::gregorian::date& query_date) const override;

 private:
  boost::gregorian::date AdjustHoliday(
      const boost::gregorian::date& holiday) const;
  boost::gregorian::date NewYearsDay(int year) const;
  static boost::gregorian::date GoodFriday(int year);
  static boost::gregorian::date EasterMonday(int year);
  boost::gregorian::date EarlyMayBankHoliday(int year) const;
  static boost::gregorian::date SpringBankHoliday(int year);
  static boost::gregorian::date SummerBankHoliday(int year);
  boost::gregorian::date ChristmasDay(int year) const;
  boost::gregorian::date BoxingDay(int year) const;
};
}  // namespace qff_a