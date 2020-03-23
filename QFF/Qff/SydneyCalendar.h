#pragma once
#include "BaseCalendar.h"

namespace qff_a {
// NSW business days are weekdays (Monday to Friday) other than NSW public
// holidays as gazetted under the NSW state government’s Banks and Bank Holidays
// Act 1912.
class SydneyCalendar final : public BaseCalendar {
 public:
  std::unique_ptr<ICalendar> Clone() const override;
  bool IsHoliday(const boost::gregorian::date& query_date) const override;

 private:
  boost::gregorian::date AdjustHoliday(
      const boost::gregorian::date& holiday) const;
  boost::gregorian::date NewYearsDay(int year) const;
  boost::gregorian::date AustraliaDay(int year) const;
  static boost::gregorian::date GoodFriday(int year);
  static boost::gregorian::date EasterMonday(int year);
  static boost::gregorian::date AnzacDay(int year);
  static boost::gregorian::date QueensBirthday(int year);
  static boost::gregorian::date BankHoliday(int year);
  static boost::gregorian::date LabourDay(int year);
  boost::gregorian::date ChristmasDay(int year) const;
  boost::gregorian::date BoxingDay(int year) const;
};
}  // namespace qff_a
