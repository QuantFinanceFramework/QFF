#pragma once
#include <memory>
#include <string>
#include "IBusinessDayConvention.h"
#include "ICalendar.h"
#include "IDayCounter.h"
#include "IIndex.h"
#include "Period.h"
namespace qff {
using std::string;
using std::unique_ptr;

class OvernightIndex : public IIndex {
 public:
  OvernightIndex() = default;
  OvernightIndex(const string& currencyCode, const string& curveName,
                 Period tenor, const IDayCounter& dayCounter, Period fixingLag,
                 Period publicationLag, const ICalendar& fixingCalendar,
                 const IBusinessDayConvention& convention);

  ~OvernightIndex() = default;

  unique_ptr<IIndex> clone() const override;

  double getRate(const date& startDate,
                 const IMarketData& marketData) const override;

 private:
  date getFixingDate(const date& startDate) const;

  string currencyCode_;
  string curveName_;
  Period tenor_;
  unique_ptr<IDayCounter> dayCounter_;
  Period fixingLag_;
  Period publicationLag_;
  unique_ptr<ICalendar> fixingCalendar_;
  unique_ptr<IBusinessDayConvention> convention_;
};
}  // namespace qff