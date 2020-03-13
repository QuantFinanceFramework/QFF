#pragma once
#include "BaseCalendar.h"

namespace qff_a {
// SIFMA holiday recommendations apply to the trading of U.S. dollar-denominated
// government securities, mortgage- and asset-backed securities,
// over-the-counter investment-grade and high-yield corporate bonds, municipal
// bonds and secondary money market trading in bankers' acceptances, commercial
// paper and Yankee and Euro certificates of deposit.
class UsBondMarketCalendar final : public BaseCalendar {
 public:
  std::unique_ptr<ICalendar> Clone() const override;
  bool IsHoliday(const boost::gregorian::date& query_date) const override;

 private:
  boost::gregorian::date AdjustHoliday(
      const boost::gregorian::date& holiday) const;
  static boost::gregorian::date NewYearsDay(int year);
  boost::gregorian::date MartinLutherKingsBirthday(int year) const;
  boost::gregorian::date WashingtonsBirthday(int year) const;
  static boost::gregorian::date GoodFriday(int year);
  static boost::gregorian::date EasterMonday(int year);
  static boost::gregorian::date MemorialDay(int year);
  boost::gregorian::date IndependenceDay(int year) const;
  boost::gregorian::date LabourDay(int year) const;
  boost::gregorian::date ColumbusDay(int year) const;
  boost::gregorian::date VeteransDay(int year) const;
  boost::gregorian::date ThanksgivingDay(int year) const;
  boost::gregorian::date ChristmasDay(int year) const;
};
}  // namespace qff_a