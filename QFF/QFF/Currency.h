#pragma once
#include <string>

namespace qff {
using std::string;

struct Currency {
 public:
  Currency() = default;
  Currency(string currency_code, double amount);
  ~Currency() = default;

  string currency_code;
  double amount;
};
}  // namespace qff