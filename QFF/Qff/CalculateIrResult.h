#pragma once
#include "Currency.h"
#include "IPricingEnvironment.h"
#include "IProduct.h"
#include "IrResult.h"

namespace qff_a {
inline IrResult CalculateIrResult(
    const IProduct& product,
    const IPricingEnvironment<aad::a_double>& environment,
    const std::string& valuation_currency) {
  auto tape = *aad::a_double::tape;
  tape.clear();
  environment.PutInterestRateCurvesOnTape();
  auto result = product.Evaluate(environment, valuation_currency);
  result.amount.propagate_to_start();
  auto deltas = environment.GetInterestRateAdjoints();
  tape.rewind();
  return IrResult{Currency(result.currency_code, result.amount.value()),
                  std::move(deltas)};
}
}  // namespace qff_a
