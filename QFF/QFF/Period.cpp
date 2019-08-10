#include "Period.h"
#include <memory>
#include "Following.h"
#include "Preceding.h"

namespace qff {
Period::Period(int length, TimeUnit unit) : length(length), unit(unit) {}

Period& Period::operator+=(const Period& rhs) {
  if (this->unit == rhs.unit) {
    this->length += rhs.length;
    return *this;
  }
  throw std::logic_error{"Different unit used in Period arithmetic"};
}
Period& Period::operator-=(const Period& rhs) {
  if (this->unit == rhs.unit) {
    this->length -= rhs.length;
    return *this;
  }
  throw std::logic_error{"Different unit used in Period arithmetic"};
}

Period& Period::operator-() {
  this->length *= -1;
  return *this;
}

Period operator+(const Period& lhs, const Period& rhs) {
  if (lhs.unit == rhs.unit) return Period(lhs.length + rhs.length, lhs.unit);
  throw std::logic_error{"Different unit used in Period arithmetic"};
}

Period operator-(const Period& lhs, const Period& rhs) {
  if (lhs.unit == rhs.unit) return Period(lhs.length - rhs.length, lhs.unit);
  throw std::logic_error{"Different unit used in Period arithmetic"};
}

Period operator-(const Period& rhs) { return Period(-rhs.length, rhs.unit); }

date ShiftDate(const date& original_date, const Period& period,
               const ICalendar& calendar,
               const IBusinessDayConvention& convention) {
  switch (period.unit) {
    case TimeUnit::d:
      return convention.Adjust(
          original_date + boost::gregorian::days(period.length), calendar);
    case TimeUnit::w:
      return convention.Adjust(
          original_date + boost::gregorian::weeks(period.length), calendar);
    case TimeUnit::m:
      return convention.Adjust(
          original_date + boost::gregorian::months(period.length), calendar);
    case TimeUnit::y:
      return convention.Adjust(
          original_date + boost::gregorian::years(period.length), calendar);
    case TimeUnit::b:
      auto length = period.length;
      if (length > 0) {
        const auto following = std::make_unique<Following>();
        auto tmp_date = original_date;
        do {
          tmp_date =
              following->Adjust(tmp_date + boost::gregorian::days(1), calendar);
          length--;
        } while (length > 0);
        return tmp_date;
      }
      if (length < 0) {
        const auto preceding = std::make_unique<Preceding>();
        auto tmp_date = original_date;
        do {
          tmp_date =
              preceding->Adjust(tmp_date - boost::gregorian::days(1), calendar);
          length++;
        } while (length < 0);
        return tmp_date;
      }

      return original_date;
  }
  throw std::invalid_argument("invalid TimeUnit");
}
}  // namespace qff
