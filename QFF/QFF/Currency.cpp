#include "Currency.h"
#include <stdexcept>

namespace qff {
Currency::Currency(string currency_code, double amount)
    : currency_code(std::move(currency_code)), amount(amount) {}

Currency& Currency::operator+=(const Currency& rhs) {
  if (this->currency_code == rhs.currency_code) {
    this->amount += rhs.amount;
    return *this;
  }
  throw std::logic_error{"Different currency code used in Currency arithmetic"};
}

Currency& Currency::operator-=(const Currency& rhs) {
  if (this->currency_code == rhs.currency_code) {
    this->amount -= rhs.amount;
    return *this;
  }
  throw std::logic_error{"Different currency code used in Currency arithmetic"};
}

Currency operator+(const Currency& lhs, const Currency& rhs) {
  if (lhs.currency_code == rhs.currency_code)
    return Currency(lhs.currency_code, lhs.amount + rhs.amount);
  throw std::logic_error{"Different currency code used in Currency arithmetic"};
}

Currency operator-(const Currency& lhs, const Currency& rhs) {
  if (lhs.currency_code == rhs.currency_code)
    return Currency(lhs.currency_code, lhs.amount - rhs.amount);
  throw std::logic_error{"Different currency code used in Currency arithmetic"};
}
}  // namespace qff