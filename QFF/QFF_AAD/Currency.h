#pragma once
#include <stdexcept>
#include <string>

namespace qff_a {
template <typename T>
struct Currency {
  Currency() = default;
  Currency(std::string currency_code, T amount);

  Currency& operator+=(const Currency& rhs);
  Currency& operator-=(const Currency& rhs);

  std::string currency_code;
  T amount{};
};

template <typename T>
Currency<T>::Currency(std::string currency_code, T amount)
    : currency_code(std::move(currency_code)), amount(std::move(amount)) {}

template <typename T>
Currency<T>& Currency<T>::operator+=(const Currency& rhs) {
  if (this->currency_code == rhs.currency_code) {
    this->amount += rhs.amount;
    return *this;
  }
  throw std::logic_error{"Different currency code used in Currency arithmetic"};
}

template <typename T>
Currency<T>& Currency<T>::operator-=(const Currency& rhs) {
  if (this->currency_code == rhs.currency_code) {
    this->amount -= rhs.amount;
    return *this;
  }
  throw std::logic_error{"Different currency code used in Currency arithmetic"};
}

template <typename T>
Currency<T> operator+(const Currency<T>& lhs, const Currency<T>& rhs) {
  if (lhs.currency_code == rhs.currency_code)
    return Currency(lhs.currency_code, T(lhs.amount + rhs.amount));
  throw std::logic_error{"Different currency code used in Currency arithmetic"};
}

template <typename T>
Currency<T> operator-(const Currency<T>& lhs, const Currency<T>& rhs) {
  if (lhs.currency_code == rhs.currency_code)
    return Currency(lhs.currency_code, T(lhs.amount - rhs.amount));
  throw std::logic_error{"Different currency code used in Currency arithmetic"};
}
}  // namespace qff_a