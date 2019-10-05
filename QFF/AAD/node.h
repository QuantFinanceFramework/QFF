#pragma once
#include <algorithm>

namespace aad {
class node {
 public:
  explicit node(const size_t n = 0)
      : p_adjoints_(nullptr),
        p_derivatives_(nullptr),
        p_adj_ptrs_(nullptr),
        num_arg_(n) {}

  //  Access to adjoint(s)
  //	single
  double& adjoint() { return adjoint_; }
  //	multi
  [[nodiscard]] double& adjoint(const size_t n) const { return p_adjoints_[n]; }

  //  Back-propagate adjoints to arguments adjoints

  //  Single case
  void propagate_one() const {
    //  Nothing to propagate
    if (!num_arg_ || !adjoint_) return;

    for (size_t i = 0; i < num_arg_; ++i) {
      *(p_adj_ptrs_[i]) += p_derivatives_[i] * adjoint_;
    }
  }

  //  Multi case
  void propagate_all() const {
    //  No adjoint to propagate
    if (!num_arg_ || std::all_of(p_adjoints_, p_adjoints_ + num_adj_,
                                 [](const double& x) { return !x; }))
      return;

    for (size_t i = 0; i < num_arg_; ++i) {
      const auto adj_ptr = p_adj_ptrs_[i];
      const auto derivative = p_derivatives_[i];

      //  Vectorized!
      for (size_t j = 0; j < num_adj_; ++j) {
        adj_ptr[j] += derivative * p_adjoints_[j];
      }
    }
  }

private:
  friend class tape;
  friend class aad_double;
  friend auto set_num_results_for_aad(bool, size_t);
  friend struct num_results_resetter_for_aad;

  //  The adjoint(s)
  //	in single case, self held
  double adjoint_ = 0;
  //	in multi case, held separately and accessed by pointer
  double* p_adjoints_;

  //  Data lives in separate memory

  //  the n derivatives to arguments,
  double* p_derivatives_;

  //  the n pointers to the adjoints of arguments
  double** p_adj_ptrs_;

  //  Number of adjoints (results) to propagate, usually 1
  static size_t num_adj_;

  //  Number of children (arguments)
  const size_t num_arg_;
};
}  // namespace aad