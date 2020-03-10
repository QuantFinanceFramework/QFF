#include "IrResult.h"

namespace qff_a {
IrResult::IrResult(double npv, IrDeltas deltas)
    : npv_(npv), deltas_(std::move(deltas)) {}

double IrResult::GetNpv() const { return npv_; }

IrDeltas IrResult::GetIrDeltas() const { return deltas_; }

void IrResult::PrintDeltas() const { deltas_.PrintDeltas(); }
}  // namespace qff_a
