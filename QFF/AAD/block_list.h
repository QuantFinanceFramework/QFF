#pragma once
#include <array>
#include <iterator>
#include <list>
#include <utility>

namespace aad {
template <typename T, size_t BlockSize>
class block_list {
 public:
  using list_iterator = typename std::list<std::array<T, BlockSize>>::iterator;
  using block_iterator = typename std::array<T, BlockSize>::iterator;
  //  Create first block on construction
  block_list() { new_block(); }

  //  Factory reset
  void clear() {
    data_.clear();
    new_block();
  }

  //  Rewind but keep all blocks
  void rewind() {
    cur_block_ = data_.begin();
    next_space_ = cur_block_->begin();
    last_space_ = cur_block_->end();
  }

  //	Memset
  void memset(const unsigned char value = 0) {
    for (auto& arr : data_) {
      std::memset(&arr[0], value, BlockSize * sizeof(T));
    }
  }

  //  Construct object of type T in place
  //      in the next free space and return a pointer on it
  //  Implements perfect forwarding of constructor arguments
  template <typename... Args>
  T* emplace_back(Args&&... args) {
    //  No more space in current array
    if (next_space_ == last_space_) {
      next_block();
    }
    //  Placement new, construct in memory pointed by next
    T* emplaced = new (&*next_space_)  //  memory pointed by next as T*
        T(std::forward<Args>(
            args)...);  //  perfect forwarding of ctor arguments

    //  Advance next
    ++next_space_;

    //  Return
    return emplaced;
  }

  //  Overload for default constructed
  T* emplace_back() {
    //  No more space in current array
    if (next_space_ == last_space_) {
      next_block();
    }

    //  Current space
    auto old_next = next_space_;

    //  Advance next
    ++next_space_;

    //  Return
    return &*old_next;
  }

  //  Stores n default constructed elements
  //      and returns a pointer on the first

  //	Version 1: n known at compile time
  template <size_t N>
  T* emplace_back_multi() {
    //  No more space in current array
    if (std::distance(next_space_, last_space_) < N) {
      next_block();
    }

    //  Current space
    auto old_next = next_space_;

    //  Advance next
    next_space_ += N;

    //  Return
    return &*old_next;
  }

  //	Version 2: n unknown at compile time
  T* emplace_back_multi(const size_t n) {
    //  No more space in current array
    if (std::distance(next_space_, last_space_) < n) {
      next_block();
    }

    //  Current space
    auto old_next = next_space_;

    //  Advance next
    next_space_ += n;

    //  Return
    return &*old_next;
  }

  //  Set mark
  void set_mark() {
    marked_block_ = cur_block_;
    marked_space_ = next_space_;
  }

  //  Rewind to mark
  void rewind_to_mark() {
    cur_block_ = marked_block_;
    next_space_ = marked_space_;
    last_space_ = cur_block_->end();
  }

  //  Iterator

  class iterator {
   public:
    //  iterator traits
    using difference_type = ptrdiff_t;
    using reference = T&;
    using pointer = T*;
    using value_type = T;
    using iterator_category = std::bidirectional_iterator_tag;

    //	Default constructor
    iterator() = default;

    //	Constructor
    iterator(list_iterator cb, block_iterator cs, block_iterator fs, block_iterator ls)
        : cur_block_(std::move(cb)),
          cur_space_(std::move(cs)),
          first_space_(std::move(fs)),
          last_space_(std::move(ls)) {}

    //	Pre-increment (we do not provide post)
    iterator& operator++() {
      ++cur_space_;
      if (cur_space_ == last_space_) {
        ++cur_block_;
        first_space_ = cur_block_->begin();
        last_space_ = cur_block_->end();
        cur_space_ = first_space_;
      }

      return *this;
    }

    //	Pre-decrement
    iterator& operator--() {
      if (cur_space_ == first_space_) {
        --cur_block_;
        first_space_ = cur_block_->begin();
        last_space_ = cur_block_->end();
        cur_space_ = last_space_;
      }

      --cur_space_;

      return *this;
    }

    //	Access to contained elements
    T& operator*() { return *cur_space_; }
    const T& operator*() const { return *cur_space_; }
    T* operator->() { return &*cur_space_; }
    const T* operator->() const { return &*cur_space_; }

    //	Check equality
    bool operator==(const iterator& rhs) const {
      return (cur_block_ == rhs.cur_block_ && cur_space_ == rhs.cur_space_);
    }
    bool operator!=(const iterator& rhs) const {
      return (cur_block_ != rhs.cur_block_ || cur_space_ != rhs.cur_space_);
    }

  private:
    //  List and block
    list_iterator cur_block_;     //  current block
    block_iterator cur_space_;    //  current space
    block_iterator first_space_;  //  first space in block
    block_iterator last_space_;   //  last (+1) space in block
  };

  //  Access to iterators

  iterator begin() {
    return iterator(data_.begin(), data_.begin()->begin(),
                    data_.begin()->begin(), data_.begin()->end());
  }

  iterator end() {
    auto last_block = std::prev(data_.end());
    return iterator(cur_block_, next_space_, cur_block_->begin(),
                    cur_block_->end());
  }

  //  Iterator on mark
  iterator mark() {
    return iterator(marked_block_, marked_space_, marked_block_->begin(),
                    marked_block_->end());
  }

  //  Find element, by pointer, searching sequentially from the end
  iterator find(const T* const element) {
    //	Search from the end
    auto it = end();
    auto b = begin();

    while (it != b) {
      --it;
      if (&*it == element) return it;
    }

    if (&*it == element) return it;

    return end();
  }

 private:
  //  Create new array
  void new_block() {
    data_.emplace_back();
    cur_block_ = last_block_ = std::prev(data_.end());
    next_space_ = cur_block_->begin();
    last_space_ = cur_block_->end();
  }

  //  Move on to next array
  void next_block() {
    //  This is the last array: create new
    if (cur_block_ == last_block_) {
      new_block();
    } else {
      ++cur_block_;
      next_space_ = cur_block_->begin();
      last_space_ = cur_block_->end();
    }
  }
  std::list<std::array<T, BlockSize>> data_;

  //  Current block
  list_iterator cur_block_;

  //  Last block
  list_iterator last_block_;

  //  Next free space in current block
  block_iterator next_space_;

  //  Last free space (+1) in current block
  block_iterator last_space_;

  //  Mark
  list_iterator marked_block_;
  block_iterator marked_space_;
};
}  // namespace aad
