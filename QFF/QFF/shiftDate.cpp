#include "shiftDate.h"
#include "Following.h"
#include "Preceding.h"
#include "Unadjusted.h"
#include <memory>

namespace qff {
date shiftDate(date originalDate, int length, TimeUnit timeUnit,
               const ICalendar& calendar,
               const IBusinessDayConvention& convention) {
  switch (timeUnit) {
    case TimeUnit::d:
      return convention.adjust(originalDate + boost::gregorian::days(length),
                               calendar);
    case TimeUnit::w:
      return convention.adjust(originalDate + boost::gregorian::weeks(length),
                               calendar);
    case TimeUnit::m:
      return convention.adjust(originalDate + boost::gregorian::months(length),
                               calendar);
    case TimeUnit::y:
      return convention.adjust(originalDate + boost::gregorian::years(length),
                               calendar);
    case TimeUnit::b:
      if (length > 0) {
        auto following = std::make_unique<Following>();
        auto a = following->adjust(originalDate, calendar);
        date tmpDate = originalDate;
        do {
          tmpDate = following->adjust(tmpDate + boost::gregorian::days(1),
                                      calendar);
          length--;
        } while (length > 0);
        return tmpDate;
      }
      if (length < 0) {
        auto preceding = std::make_unique<Preceding>();
        date tmpDate = originalDate;
        do {
          tmpDate = preceding->adjust(tmpDate - boost::gregorian::days(1),
                                      calendar);
          length++;
        } while (length < 0);
        return tmpDate;

        return originalDate;
      }
  }
}
}  // namespace qff