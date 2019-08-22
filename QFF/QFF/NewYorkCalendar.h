#pragma once
#include "BaseCalendar.h"

namespace qff {
class NewYorkCalendar : public BaseCalendar {
 public:
  std::unique_ptr<ICalendar> Clone() const override;
  bool IsHoliday(const boost::gregorian::date& query_date) const override;

 protected:
  boost::gregorian::date AdjustHoliday(
      const boost::gregorian::date& holiday) const override;

 private:
  boost::gregorian::date MartinLutherKingsBirthday(int year) const;
  boost::gregorian::date WashingtonsBirthday(int year) const;
  static boost::gregorian::date MemorialDay(int year);
  boost::gregorian::date IndependenceDay(int year) const;
  boost::gregorian::date LabourDay(int year) const;
  boost::gregorian::date ColumbusDay(int year) const;
  boost::gregorian::date VeteransDay(int year) const;
  boost::gregorian::date ThanksgivingDay(int year) const;
};
}  // namespace qff