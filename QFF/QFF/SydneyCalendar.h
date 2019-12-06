#pragma once
#include "BaseCalendar.h"

namespace qff {
class SydneyCalendar final : public BaseCalendar {
 public:
  std::unique_ptr<ICalendar> Clone() const override;
  bool IsHoliday(const boost::gregorian::date& query_date) const override;

 private:
  boost::gregorian::date AustraliaDay(int year) const;
  boost::gregorian::date AnzacDay(int year) const;
  static boost::gregorian::date QueensBirthday(int year);
  static boost::gregorian::date BankHoliday(int year);
  static boost::gregorian::date LabourDay(int year);
};
}  // namespace qff
