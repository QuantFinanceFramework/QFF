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

class IborIndex : public IIndex {
 public:
  IborIndex() = default;
  IborIndex(string curveName, Period tenor, Period fixingOffset,
            const ICalendar& fixingCalendar,
            const IBusinessDayConvention& convention,
            const IDayCounter& dayCounter, bool preserveEndofMonth);

  ~IborIndex() = default;

  unique_ptr<IIndex> clone() const override;

  double getRate(const date& startDate,
                 const IMarketData& marketData) const override;

 private:
  date getFixingDate(const date& startDate) const;

  string curveName_;
  Period tenor_;
  Period fixingOffset_;
  unique_ptr<ICalendar> fixingCalendar_;
  unique_ptr<IBusinessDayConvention> convention_;
  unique_ptr<IDayCounter> dayCounter_;
  bool preserveEndofMonth_;
};
}  // namespace qff
