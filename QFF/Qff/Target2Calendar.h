#pragma once
#include "BaseCalendar.h"

namespace qff_a {
class Target2Calendar final : public BaseCalendar {
 public:
  std::unique_ptr<ICalendar> Clone() const override;
  bool IsHoliday(const boost::gregorian::date& query_date) const override;

 private:
  static boost::gregorian::date NewYearsDay(int year);
  static boost::gregorian::date GoodFriday(int year);
  static boost::gregorian::date EasterMonday(int year);
  static boost::gregorian::date LabourDay(int year);
  static boost::gregorian::date ChristmasDay(int year);
  static boost::gregorian::date BoxingDay(int year);
};
}  // namespace qff_a
