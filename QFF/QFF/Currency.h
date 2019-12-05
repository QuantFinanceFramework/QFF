#pragma once
#include <string>

namespace qff {
struct Currency {
  Currency() = default;
  Currency(std::string currency_code, double amount);

  Currency& operator+=(const Currency& rhs);
  Currency& operator-=(const Currency& rhs);

  std::string currency_code;
  double amount{};
};

Currency operator+(const Currency& lhs, const Currency& rhs);

Currency operator-(const Currency& lhs, const Currency& rhs);

}  // namespace qff