#pragma once
#include <vector>

#include "IPricingEnvironment.h"
#include "IProduct.h"

namespace qff_a {

std::vector<std::vector<double>> GenerateInterestRateDeltas(
    const IProduct& product,
    const IPricingEnvironment<aad::a_double>& environment,
    const std::string& currency_code) {
  auto tape = *aad::a_double::tape;
  tape.clear();
  environment.PutInterestRateCurvesOnTape();
  auto result = product.Evaluate(environment, currency_code);
  result.propagate_to_start();
  auto adjoints = environment.GetInterestRateAdjoints();
  tape.rewind();
  return adjoints;
}
}  // namespace qff_a
