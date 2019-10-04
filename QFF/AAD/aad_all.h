#pragma once
#include "expression.h"

namespace aad {
struct num_results_resetter_for_aad {
  ~num_results_resetter_for_aad() {
    tape::is_multi_ = false;
    node::num_adj_ = 1;
  }
}; 

//  Routine: set dimension and get RAII resetter
inline auto set_num_results_for_aad(const bool is_multi = false,
                                    const size_t num_results = 1) {
  tape::is_multi_ = is_multi;
  node::num_adj_ = num_results;
  return std::make_unique<num_results_resetter_for_aad>();
}

//  Other utilities

//	Put collection on tape
template <typename It>
void put_on_tape(It begin, It end) {
  std::for_each(begin, end, [](aad_double& n) { n.put_on_tape(); });
}

//	Convert collection between double and Number or reverse
template <typename It1, typename It2>
void convert_collection(It1 src_begin, It1 src_end, It2 dest_begin) {
  using dest_type = std::remove_reference_t<decltype(*dest_begin)>;
  std::transform(src_begin, src_end, dest_begin,
                 [](const auto& source) { return dest_type(source); });
}
}  // namespace aad