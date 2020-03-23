#include "Period.h"
#include "Preceding.h"

namespace qff_a {
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

}  // namespace qff_a
