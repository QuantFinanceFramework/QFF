#include "IrResult.h"

#include <utility>

namespace qff_a {
IrResult::IrResult(Currency<double> npv, IrDeltas deltas)
    : npv_(std::move(npv)), deltas_(std::move(deltas)) {}

double IrResult::GetNpv() const { return npv_.amount; }

std::string IrResult::GetResultCurrency() const { return npv_.currency_code; }

IrDeltas IrResult::GetIrDeltas() const { return deltas_; }

void IrResult::PrintDeltas() const { deltas_.PrintDeltas(); }
}  // namespace qff_a
