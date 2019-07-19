#include "Currency.h"

namespace qff {
Currency::Currency(string currencyCode, double amount)
    : currencyCode(currencyCode), amount(amount) {}
}  // namespace qff