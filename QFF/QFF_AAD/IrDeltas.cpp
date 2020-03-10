#include "IrDeltas.h"
#include <iostream>
#include <numeric>
#include <tuple>

namespace qff_a {

void IrDeltas::Append(IrDeltas rhs) {
  std::copy(std::make_move_iterator(begin(rhs.pillars_)),
            std::make_move_iterator(end(rhs.pillars_)),
            std::back_inserter(pillars_));
  std::copy(std::make_move_iterator(begin(rhs.deltas_)),
            std::make_move_iterator(end(rhs.deltas_)),
            std::back_inserter(deltas_));
}

void IrDeltas::PrintDeltas() const {
  for (auto [p, d] = std::tuple{pillars_.begin(), deltas_.begin()};
       p != pillars_.end() && d != deltas_.end(); ++p, ++d) {
    std::cout << *p << ": " << *d * 0.0001 << '\n';
  }
}

IrDeltas::IrDeltas(std::vector<std::string> pillars, std::vector<double> deltas)
    : pillars_(std::move(pillars)), deltas_(std::move(deltas)) {}
}  // namespace qff_a
