#pragma once
#include "node.h"
#include "block_list.h"

namespace aad {
constexpr size_t block_size = 16384;    //	Number of nodes
constexpr size_t adjoint_size = 32768;  //	Number of adjoints
constexpr size_t data_size = 65536;     //	Data in bytes

class tape {
 public:
  //  Build note in place and return a pointer
  //	N : a_double of children (arguments)
  template <size_t N>
  node* record_node() {
    //  Construct the node in place on tape
    const auto node = nodes_.emplace_back(N);

    //  Store and zero the adjoint(s)
    if (is_multi_) {
      node->p_adjoints_ = adjoints_multi_.emplace_back_multi(node::num_adj_);
      std::fill(node->p_adjoints_, node->p_adjoints_ + node::num_adj_, 0.0);
    }

    //	Store the derivatives and child adjoint pointers unless leaf
    if constexpr (N) {
      node->p_derivatives_ = derivatives_.emplace_back_multi<N>();
      node->p_adj_ptrs_ = adjoint_ptrs_.emplace_back_multi<N>();
    }

    return node;
  }

  //  Reset all adjoints to 0
  void reset_adjoints() {
    if (is_multi_) {
      adjoints_multi_.memset(0);
    } else {
      for (auto& node : nodes_) {
        node.adjoint_ = 0;
      }
    }
  }

  //  Clear
  void clear() {
    adjoints_multi_.clear();
    derivatives_.clear();
    adjoint_ptrs_.clear();
    nodes_.clear();
  }

  //  Rewind
  void rewind() {
#ifdef _DEBUG

    //  In debug mode, always wipe
    //      makes it easier to identify errors

    clear();

#else
    //  In release mode, rewind and reuse

    if (is_multi_) {
      adjoints_multi_.rewind();
    }
    derivatives_.rewind();
    adjoint_ptrs_.rewind();
    nodes_.rewind();

#endif
  }

  //  Set mark
  void mark() {
    if (is_multi_) {
      adjoints_multi_.set_mark();
    }
    derivatives_.set_mark();
    adjoint_ptrs_.set_mark();
    nodes_.set_mark();
  }

  //  Rewind to mark
  void rewind_to_mark() {
    if (is_multi_) {
      adjoints_multi_.rewind_to_mark();
    }
    derivatives_.rewind_to_mark();
    adjoint_ptrs_.rewind_to_mark();
    nodes_.rewind_to_mark();
  }

  //  iterators

  using iterator = block_list<node, block_size>::iterator;

  auto begin() { return nodes_.begin(); }

  auto end() { return nodes_.end(); }

  auto mark_it() { return nodes_.mark(); }

  auto find(node* node) { return nodes_.find(node); }

private:
  //	Working with multiple results / adjoints?
  static bool is_multi_;

  //  Storage for adjoints in multi-dimensional case
  block_list<double, adjoint_size> adjoints_multi_;

  //  Storage for derivatives and child adjoint pointers
  block_list<double, data_size> derivatives_;
  block_list<double*, data_size> adjoint_ptrs_;

  //  Storage for the nodes
  block_list<node, block_size> nodes_;

  //	Padding so tapes in a vector don't interfere
  char pad_[64]{};

  friend auto set_num_results_for_aad(bool, size_t);
  friend struct num_results_resetter_for_aad;
  friend class a_double;
};
}  // namespace aad