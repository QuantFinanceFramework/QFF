#pragma once
#include "IPricingEnvironment.h"
#include "IProduct.h"
#include "IrResult.h"

namespace qff_a {
inline IrResult CalculateIrResult(
    const IProduct& product,
    const IPricingEnvironment<aad::a_double>& environment,
    const std::string& currency_code) {
  auto tape = *aad::a_double::tape;
  tape.clear();
  environment.PutInterestRateCurvesOnTape();
  auto result = product.Evaluate(environment, currency_code);
  result.propagate_to_start();
  auto deltas = environment.GetInterestRateAdjoints();
  tape.rewind();
  return IrResult{result.value(), std::move(deltas)};
}
}  // namespace qff_a
