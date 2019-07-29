#pragma once
#include <string>

namespace qff {
using std::string;

struct Currency {
  Currency() = default;
  Currency(string currency_code, double amount);
  ~Currency() = default;

  Currency& operator+=(const Currency& rhs);
  Currency& operator-=(const Currency& rhs);

  string currency_code;
  double amount{};
};

Currency operator+(const Currency& lhs, const Currency& rhs);

Currency operator-(const Currency& lhs, const Currency& rhs);

}  // namespace qff