#pragma once
#include "BaseCalendar.h"

namespace qff_a {
// Federal Reserve Bank of New York calendar
class NewYorkFedCalendar final : public BaseCalendar {
 public:
  std::unique_ptr<ICalendar> Clone() const override;
  bool IsHoliday(const boost::gregorian::date& query_date) const override;

 private:
  boost::gregorian::date AdjustHoliday(
      const boost::gregorian::date& holiday) const;
  boost::gregorian::date NewYearsDay(int year) const;
  boost::gregorian::date MartinLutherKingsBirthday(int year) const;
  boost::gregorian::date WashingtonsBirthday(int year) const;
  static boost::gregorian::date MemorialDay(int year);
  boost::gregorian::date IndependenceDay(int year) const;
  boost::gregorian::date LabourDay(int year) const;
  boost::gregorian::date ColumbusDay(int year) const;
  boost::gregorian::date VeteransDay(int year) const;
  boost::gregorian::date ThanksgivingDay(int year) const;
  boost::gregorian::date ChristmasDay(int year) const;
};
}  // namespace qff_a