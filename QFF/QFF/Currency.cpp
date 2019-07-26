#include "Currency.h"

namespace qff {
Currency::Currency(const string& currency_code, double amount)
    : currency_code(currency_code), amount(amount) {}
}  // namespace qff