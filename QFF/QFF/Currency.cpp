#include "Currency.h"
#include <utility>

namespace qff {
Currency::Currency(string currency_code, double amount)
    : currency_code(std::move(currency_code)), amount(amount) {}
}  // namespace qff