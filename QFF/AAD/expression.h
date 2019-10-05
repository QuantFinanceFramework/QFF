#pragma once
#include <cmath>
#include "tape.h"
#include "gaussians.h"

namespace aad {
//  Base CRTP expression class
template <typename Expression>
class expression {
public:
  [[nodiscard]] double value() const {
    return static_cast<const Expression*>(this)->value();
  }

  explicit operator double() const { return value(); }
};

//  Note that aad_double is a leaf expression
//  Defined in the bottom of the file

//  Binary expression
//  LeftExpression : the expression on the left
//  Expression : the expression on the right
//  Operator : the binary operator
template <typename LeftExpression, typename RightExpression, typename Operator>
class binary_expression
    //  CRTP
    : public expression<
          binary_expression<LeftExpression, RightExpression, Operator>> {
 public:
  //  Constructor out of 2 expressions
  //  Note: eager evaluation on construction
  explicit binary_expression(const expression<LeftExpression>& l,
                             const expression<RightExpression>& r)
      : value_(Operator::eval(l.value(), r.value())),
        lhs_(static_cast<const LeftExpression&>(l)),
        rhs_(static_cast<const RightExpression&>(r)) {}

  //  Value accessors
  [[nodiscard]] double value() const { return value_; }

  //	Expression template magic
  //  Expressions know
  //  AT COMPILE TIME
  //  the number of active inputs in their sub-expressions
  enum {
    num_actives = LeftExpression::num_actives + RightExpression::num_actives
  };

  //  Push adjoint down the expression
  //  TotalActives : total number of active inputs in the expression
  //  ProcessedActives : number of active inputs already processed
  template <size_t TotalActives, size_t ProcessedActives>
  void push_adjoint(
      //  Node for the complete expression being processed
      node& expr_node,
      //  Adjoint accumulated for this binary node, or 1 if top
      const double adjoint) const {
    //  Push on the left
    if (LeftExpression::num_actives > 0) {
      lhs_.push_adjoint<TotalActives, ProcessedActives>(
          expr_node,
          adjoint * Operator::left_derivative(lhs_.value(), rhs_.value(), value()));
    }

    //  Push on the right
    if (RightExpression::num_actives > 0) {
      //  Note left push processed LeftExpression::num_actives numbers
      //  So the next aad_double to be processed is ProcessedActives +
      //  LeftExpression::num_actives
      rhs_.push_adjoint<TotalActives,
                        ProcessedActives + LeftExpression::num_actives>(
          expr_node,
          adjoint * Operator::right_derivative(lhs_.value(), rhs_.value(), value()));
    }
  }
private:
  const double value_;

  const LeftExpression lhs_;
  const RightExpression rhs_;
};

//  "Concrete" binaries, we only need to define operations and derivatives
struct op_multi {
  static double eval(const double l, const double r) { return l * r; }

  static double left_derivative(const double l, const double r,
                                const double v) {
    return r;
  }

  static double right_derivative(const double l, const double r,
                                 const double v) {
    return l;
  }
};

struct op_add {
  static double eval(const double l, const double r) { return l + r; }

  static double left_derivative(const double l, const double r,
                                const double v) {
    return 1.0;
  }

  static double right_derivative(const double l, const double r,
                                 const double v) {
    return 1.0;
  }
};

struct op_sub {
  static double eval(const double l, const double r) { return l - r; }

  static double left_derivative(const double l, const double r,
                                const double v) {
    return 1.0;
  }

  static double right_derivative(const double l, const double r,
                                 const double v) {
    return -1.0;
  }
};

struct op_div {
  static double eval(const double l, const double r) { return l / r; }

  static double left_derivative(const double l, const double r,
                                const double v) {
    return 1.0 / r;
  }

  static double right_derivative(const double l, const double r,
                                 const double v) {
    return -l / r / r;
  }
};

struct op_pow {
  static double eval(const double l, const double r) { return std::pow(l, r); }

  static double left_derivative(const double l, const double r,
                                const double v) {
    return r * v / l;
  }

  static double right_derivative(const double l, const double r,
                                 const double v) {
    return std::log(l) * v;
  }
};

struct op_max {
  static double eval(const double l, const double r) { return std::max(l, r); }

  static double left_derivative(const double l, const double r,
                                const double v) {
    return l > r ? 1.0 : 0.0;
  }

  static double right_derivative(const double l, const double r,
                                 const double v) {
    return r > l ? 1.0 : 0.0;
  }
};

struct op_min {
  static double eval(const double l, const double r) { return std::min(l, r); }

  static double left_derivative(const double l, const double r,
                                const double v) {
    return l < r ? 1.0 : 0.0;
  }

  static double right_derivative(const double l, const double r,
                                 const double v) {
    return r < l ? 1.0 : 0.0;
  }
};

//  Operator overloading for binary expressions`
//      build the corresponding expressions

template <typename LeftExpression, typename RightExpression>
binary_expression<LeftExpression, RightExpression, op_multi> operator*(
    const expression<LeftExpression>& lhs,
    const expression<RightExpression>& rhs) {
  return binary_expression<LeftExpression, RightExpression, op_multi>(lhs, rhs);
}

template <typename LeftExpression, typename RightExpression>
binary_expression<LeftExpression, RightExpression, op_add> operator+(
    const expression<LeftExpression>& lhs,
    const expression<RightExpression>& rhs) {
  return binary_expression<LeftExpression, RightExpression, op_add>(lhs, rhs);
}

template <typename LeftExpression, typename RightExpression>
binary_expression<LeftExpression, RightExpression, op_sub> operator-(
    const expression<LeftExpression>& lhs,
    const expression<RightExpression>& rhs) {
  return binary_expression<LeftExpression, RightExpression, op_sub>(lhs, rhs);
}

template <typename LeftExpression, typename RightExpression>
binary_expression<LeftExpression, RightExpression, op_div> operator/(
    const expression<LeftExpression>& lhs,
    const expression<RightExpression>& rhs) {
  return binary_expression<LeftExpression, RightExpression, op_div>(lhs, rhs);
}

template <typename LeftExpression, typename RightExpression>
binary_expression<LeftExpression, RightExpression, op_pow> pow(
    const expression<LeftExpression>& lhs,
    const expression<RightExpression>& rhs) {
  return binary_expression<LeftExpression, RightExpression, op_pow>(lhs, rhs);
}

template <typename LeftExpression, typename RightExpression>
binary_expression<LeftExpression, RightExpression, op_max> max(
    const expression<LeftExpression>& lhs,
    const expression<RightExpression>& rhs) {
  return binary_expression<LeftExpression, RightExpression, op_max>(lhs, rhs);
}

template <typename LeftExpression, typename RightExpression>
binary_expression<LeftExpression, RightExpression, op_min> min(
    const expression<LeftExpression>& lhs,
    const expression<RightExpression>& rhs) {
  return binary_expression<LeftExpression, RightExpression, op_min>(lhs, rhs);
}

//  Unary expressions : Same logic with one argument

//  The CRTP class
template <typename Expression, typename Operator>
class unary_expression
    //  CRTP
    : public expression<unary_expression<Expression, Operator>> {
 public:
  //  Constructor
  //  Note : eager evaluation on construction
  explicit unary_expression(const expression<Expression>& a)
      : value_(Operator::eval(a.value(), 0.0)),
        arg_(static_cast<const Expression&>(a)) {}

  //  Special constructor for binary expressions with a double on one side
  explicit unary_expression(const expression<Expression>& a, const double b)
      : value_(Operator::eval(a.value(), b)),
        arg_(static_cast<const Expression&>(a)),
        d_arg_(b) {}

  //  Value accessors
  [[nodiscard]] double value() const { return value_; }

  //	Expression template magic
  enum { num_actives = Expression::num_actives };

  //  Push adjoint down the expression
  template <size_t TotalActives, size_t ProcessedActives>
  void push_adjoint(
      //  Node for the complete expression being processed
      node& expr_node,
      //  Adjoint accumulated on the node, 1 if top
      const double adjoint) const {
    //  Push into argument
    if (Expression::num_actives > 0) {
      arg_.push_adjoint<TotalActives, ProcessedActives>(
          expr_node, adjoint * Operator::derivative(arg_.value(), value(), d_arg_));
    }
  }
private:
  const double value_;

  const Expression arg_;

  //  For binary operators with a double on one side
  //      we store the double
  const double d_arg_ = 0.0;
};

//  The unary operators

struct op_exp {
  static double eval(const double r, const double d) { return std::exp(r); }

  static double derivative(const double r, const double v, const double d) {
    return v;
  }
};

struct op_log {
  static double eval(const double r, const double d) { return std::log(r); }

  static double derivative(const double r, const double v, const double d) {
    return 1.0 / r;
  }
};

struct op_sqrt {
  static double eval(const double r, const double d) { return std::sqrt(r); }

  static double derivative(const double r, const double v, const double d) {
    return 0.5 / v;
  }
};

struct op_fabs {
  static double eval(const double r, const double d) { return std::fabs(r); }

  static double derivative(const double r, const double v, const double d) {
    return r > 0.0 ? 1.0 : -1.0;
  }
};

struct op_normal_dens {
  static double eval(const double r, const double d) { return normal_dens(r); }

  static double derivative(const double r, const double v, const double d) {
    return -r * v;
  }
};

struct op_normal_cdf {
  static double eval(const double r, const double d) { return normal_cdf(r); }

  static double derivative(const double r, const double v, const double d) {
    return normal_dens(r);
  }
};

//  Binary operators with a double on one side

//  * double or double *
struct op_multi_d {
  static double eval(const double r, const double d) { return r * d; }

  static double derivative(const double r, const double v, const double d) {
    return d;
  }
};

//  + double or double +
struct op_add_d {
  static double eval(const double r, const double d) { return r + d; }

  static double derivative(const double r, const double v, const double d) {
    return 1.0;
  }
};

//  double -
struct op_sub_dl {
  static double eval(const double r, const double d) { return d - r; }

  static double derivative(const double r, const double v, const double d) {
    return -1.0;
  }
};

//  - double
struct op_sub_dr {
  static double eval(const double r, const double d) { return r - d; }

  static double derivative(const double r, const double v, const double d) {
    return 1.0;
  }
};

//  double /
struct op_div_dl {
  static double eval(const double r, const double d) { return d / r; }

  static double derivative(const double r, const double v, const double d) {
    return -d / r / r;
  }
};

//  / double
struct op_div_dr {
  static double eval(const double r, const double d) { return r / d; }

  static double derivative(const double r, const double v, const double d) {
    return 1.0 / d;
  }
};

//  pow (d,)
struct op_pow_dl {
  static double eval(const double r, const double d) { return std::pow(d, r); }

  static double derivative(const double r, const double v, const double d) {
    return std::log(d) * v;
  }
};

//  pow (,d)
struct op_pow_dr {
  static double eval(const double r, const double d) { return std::pow(r, d); }

  static double derivative(const double r, const double v, const double d) {
    return d * v / r;
  }
};

//  max (d,)
struct op_max_d {
  static double eval(const double r, const double d) { return std::max(r, d); }

  static double derivative(const double r, const double v, const double d) {
    return r > d ? 1.0 : 0.0;
  }
};

//  min (d,)
struct op_min_d {
  static double eval(const double r, const double d) { return std::min(r, d); }

  static double derivative(const double r, const double v, const double d) {
    return r < d ? 1.0 : 0.0;
  }
};

//  And overloading

template <typename Expression>
unary_expression<Expression, op_exp> exp(const expression<Expression>& arg) {
  return unary_expression<Expression, op_exp>(arg);
}

template <typename Expression>
unary_expression<Expression, op_log> log(const expression<Expression>& arg) {
  return unary_expression<Expression, op_log>(arg);
}

template <typename Expression>
unary_expression<Expression, op_sqrt> sqrt(const expression<Expression>& arg) {
  return unary_expression<Expression, op_sqrt>(arg);
}

template <typename Expression>
unary_expression<Expression, op_fabs> fabs(const expression<Expression>& arg) {
  return unary_expression<Expression, op_fabs>(arg);
}

template <typename Expression>
unary_expression<Expression, op_normal_dens> normal_dens(
    const expression<Expression>& arg) {
  return unary_expression<Expression, op_normal_dens>(arg);
}

template <typename Expression>
unary_expression<Expression, op_normal_cdf> normal_cdf(
    const expression<Expression>& arg) {
  return unary_expression<Expression, op_normal_cdf>(arg);
}

//  Overloading continued,
//      binary operators with a double on one side

template <typename Expression>
unary_expression<Expression, op_multi_d> operator*(
    const double d, const expression<Expression>& rhs) {
  return unary_expression<Expression, op_multi_d>(rhs, d);
}

template <typename Expression>
unary_expression<Expression, op_multi_d> operator*(
    const expression<Expression>& lhs, const double d) {
  return unary_expression<Expression, op_multi_d>(lhs, d);
}

template <typename Expression>
unary_expression<Expression, op_add_d> operator+(
    const double d, const expression<Expression>& rhs) {
  return unary_expression<Expression, op_add_d>(rhs, d);
}

template <typename Expression>
unary_expression<Expression, op_add_d> operator+(
    const expression<Expression>& lhs, const double d) {
  return unary_expression<Expression, op_add_d>(lhs, d);
}

template <typename Expression>
unary_expression<Expression, op_sub_dl> operator-(
    const double d, const expression<Expression>& rhs) {
  return unary_expression<Expression, op_sub_dl>(rhs, d);
}

template <typename Expression>
unary_expression<Expression, op_sub_dr> operator-(
    const expression<Expression>& lhs, const double d) {
  return unary_expression<Expression, op_sub_dr>(lhs, d);
}

template <typename Expression>
unary_expression<Expression, op_div_dl> operator/(
    const double d, const expression<Expression>& rhs) {
  return unary_expression<Expression, op_div_dl>(rhs, d);
}

template <typename Expression>
unary_expression<Expression, op_div_dr> operator/(
    const expression<Expression>& lhs, const double d) {
  return unary_expression<Expression, op_div_dr>(lhs, d);
}

template <typename Expression>
unary_expression<Expression, op_pow_dl> pow(const double d,
                                            const expression<Expression>& rhs) {
  return unary_expression<Expression, op_pow_dl>(rhs, d);
}

template <typename Expression>
unary_expression<Expression, op_pow_dr> pow(const expression<Expression>& lhs,
                                            const double d) {
  return unary_expression<Expression, op_pow_dr>(lhs, d);
}

template <typename Expression>
unary_expression<Expression, op_max_d> max(const double d,
                                           const expression<Expression>& rhs) {
  return unary_expression<Expression, op_max_d>(rhs, d);
}

template <typename Expression>
unary_expression<Expression, op_max_d> max(const expression<Expression>& lhs,
                                           const double d) {
  return unary_expression<Expression, op_max_d>(lhs, d);
}

template <typename Expression>
unary_expression<Expression, op_min_d> min(const double d,
                                           const expression<Expression>& rhs) {
  return unary_expression<Expression, op_min_d>(rhs, d);
}

template <typename Expression>
unary_expression<Expression, op_min_d> min(const expression<Expression>& lhs,
                                           const double d) {
  return unary_expression<Expression, op_min_d>(lhs, d);
}

//  Comparison, same as traditional

template <typename LeftExpression, typename RightExpression>
bool operator==(const expression<LeftExpression>& lhs, const expression<RightExpression>& rhs) {
  return lhs.value() == rhs.value();
}
template <typename LeftExpression>
bool operator==(const expression<LeftExpression>& lhs, const double& rhs) {
  return lhs.value() == rhs;
}
template <typename LeftExpression>
bool operator==(const double& lhs, const expression<LeftExpression>& rhs) {
  return lhs == rhs.value();
}

template <typename LeftExpression, typename RightExpression>
bool operator!=(const expression<LeftExpression>& lhs, const expression<RightExpression>& rhs) {
  return lhs.value() != rhs.value();
}
template <typename LeftExpression>
bool operator!=(const expression<LeftExpression>& lhs, const double& rhs) {
  return lhs.value() != rhs;
}
template <typename LeftExpression>
bool operator!=(const double& lhs, const expression<LeftExpression>& rhs) {
  return lhs != rhs.value();
}

template <typename LeftExpression, typename RightExpression>
bool operator<(const expression<LeftExpression>& lhs, const expression<RightExpression>& rhs) {
  return lhs.value() < rhs.value();
}
template <typename LeftExpression>
bool operator<(const expression<LeftExpression>& lhs, const double& rhs) {
  return lhs.value() < rhs;
}
template <typename LeftExpression>
bool operator<(const double& lhs, const expression<LeftExpression>& rhs) {
  return lhs < rhs.value();
}

template <typename LeftExpression, typename RightExpression>
bool operator>(const expression<LeftExpression>& lhs, const expression<RightExpression>& rhs) {
  return lhs.value() > rhs.value();
}
template <typename LeftExpression>
bool operator>(const expression<LeftExpression>& lhs, const double& rhs) {
  return lhs.value() > rhs;
}
template <typename LeftExpression>
bool operator>(const double& lhs, const expression<LeftExpression>& rhs) {
  return lhs > rhs.value();
}

template <typename LeftExpression, typename RightExpression>
bool operator<=(const expression<LeftExpression>& lhs, const expression<RightExpression>& rhs) {
  return lhs.value() <= rhs.value();
}
template <typename LeftExpression>
bool operator<=(const expression<LeftExpression>& lhs, const double& rhs) {
  return lhs.value() <= rhs;
}
template <typename Expression>
bool operator<=(const double& lhs, const expression<Expression>& rhs) {
  return lhs <= rhs.value();
}

template <typename LeftExpression, typename RightExpression>
bool operator>=(const expression<LeftExpression>& lhs, const expression<RightExpression>& rhs) {
  return lhs.value() >= rhs.value();
}
template <typename Expression>
bool operator>=(const expression<Expression>& lhs, const double& rhs) {
  return lhs.value() >= rhs;
}
template <typename Expression>
bool operator>=(const double& lhs, const expression<Expression>& rhs) {
  return lhs >= rhs.value();
}

//  Finally, unary +/- operators

template <typename Expression>
unary_expression<Expression, op_sub_dl> operator-(
    const expression<Expression>& rhs) {
  return 0.0 - rhs;
}

template <typename Expression>
expression<Expression> operator+(const expression<Expression>& rhs) {
  return rhs;
}

//  The aad_double type, also an expression

class aad_double : public expression<aad_double> {
 public:
  //  Expression template magic
  enum { num_actives = 1 };

  //  Push adjoint
  //  aad_doubles are expression leaves,
  //      push_adjoint() receives their adjoint in the expression
  //  aad_doubles don't "push" anything, they register their derivatives on tape
  template <size_t TotalActives, size_t ProcessedActives>
  void push_adjoint(
      //  Node for the complete expression
      node& expr_node,
      //  Adjoint accumulated for this aad_double, in the expression
      const double adjoint) const {
    //  adjoint = d (expression) / d (thisaad_double) : register on tape
    //  note ProcessedActives: index of this aad_double on the node on tape

    //  Register adjoint
    expr_node.p_adj_ptrs_[ProcessedActives] =
        tape::is_multi_ ? node_->p_adjoints_ : &node_->adjoint_;

    //  Register derivative
    expr_node.p_derivatives_[ProcessedActives] = adjoint;
  }

  //  Static access to tape, same as traditional
  static thread_local tape* tape;

  //  Constructors

  aad_double() = default;

  explicit aad_double(const double val) : value_(val) {
    //  Create leaf
    node_ = create_multi_node<0>();
  }

  aad_double& operator=(const double val) {
    value_ = val;
    //  Create leaf
    node_ = create_multi_node<0>();
    return *this;
  }

  //  No need for copy and assignment
  //  Default ones do the right thing:
  //      copy value and pointer to node on tape

  //  Construct or assign from expression

  template <typename Expression>
  explicit aad_double(const expression<Expression>& e) : value_(e.value()) {
    //  Flatten Expression expression
    from_expr<Expression>(static_cast<const Expression&>(e));
  }

  template <typename Expression>
  aad_double& operator=(const expression<Expression>& e) {
    value_ = e.value();
    //  Flatten Expression expression
    from_expr<Expression>(static_cast<const Expression&>(e));
    return *this;
  }

  //  Explicit conversion to double
  explicit operator double&() { return value_; }
  explicit operator double() const { return value_; }

  //  All the normal accessors and propagators, same as traditional

  //  Put on tape
  void put_on_tape() { node_ = create_multi_node<0>(); }

  //  Accessors: value and adjoint

  double& value() { return value_; }
  [[nodiscard]] double value() const { return value_; }

  //  Single dimensional
  double& adjoint() { return node_->adjoint(); }
  [[nodiscard]] double adjoint() const { return node_->adjoint(); }

  //  Multi dimensional
  double& adjoint(const size_t n) { return node_->adjoint(n); }
  [[nodiscard]] double adjoint(const size_t n) const {
    return node_->adjoint(n);
  }

  //  Reset all adjoints on the tape
  //		note we don't use this method
  static void reset_adjoints() { tape->reset_adjoints(); }

  //  Propagation

  //  Propagate adjoints
  //      from and to both INCLUSIVE
  static void propagate_adjoints(const tape::iterator& propagate_from,
                                 const tape::iterator& propagate_to) {
    auto it = propagate_from;
    while (it != propagate_to) {
      it->propagate_one();
      --it;
    }
    it->propagate_one();
  }

  //  Convenient overloads

  //  Set the adjoint on this node to 1,
  //  Then propagate from the node
  void propagate_adjoints(
      //  We start on this aad_double's node
      const tape::iterator& propagate_to) {
    //  Set this adjoint to 1
    adjoint() = 1.0;
    //  Find node on tape
    auto it = tape->find(node_);
    //  Reverse and propagate until we hit the stop
    while (it != propagate_to) {
      it->propagate_one();
      --it;
    }
    it->propagate_one();
  }

  //  These 2 set the adjoint to 1 on this node
  void propagate_to_start() { propagate_adjoints(tape->begin()); }
  void propagate_to_mark() { propagate_adjoints(tape->mark_it()); }

  //  This one only propagates
  //  Note: propagation starts at mark - 1
  static void propagate_mark_to_start() {
    propagate_adjoints(std::prev(tape->mark_it()), tape->begin());
  }

  //  Multi-adjoint propagation

  //  Multi dimensional case:
  //  Propagate adjoints from and to both INCLUSIVE
  static void propagate_adjoints_multi(const tape::iterator& propagate_from,
                                       const tape::iterator& propagate_to) {
    auto it = propagate_from;
    while (it != propagate_to) {
      it->propagate_all();
      --it;
    }
    it->propagate_all();
  }

  //  Unary operators

  template <typename Expression>
  aad_double& operator+=(const expression<Expression>& e) {
    *this = *this + e;
    return *this;
  }

  template <typename Expression>
  aad_double& operator*=(const expression<Expression>& e) {
    *this = *this * e;
    return *this;
  }

  template <typename Expression>
  aad_double& operator-=(const expression<Expression>& e) {
    *this = *this - e;
    return *this;
  }

  template <typename Expression>
  aad_double& operator/=(const expression<Expression>& e) {
    *this = *this / e;
    return *this;
  }
private:
  //  Node creation on tape
  template <size_t N>
  static node* create_multi_node() {
    return tape->record_node<N>();
  }

  //  Flattening:
  //      This is where, on assignment or construction from an expression,
  //      that derivatives are pushed through the expression's DAG
  template <typename Expression>
  void from_expr(
      //  Expression expression, will be flattened into this aad_double
      const expression<Expression>& e) {
    //  Build expression node on tape
    auto* node = create_multi_node<Expression::num_actives>();

    //  Push adjoints through expression with adjoint = 1 on top
    static_cast<const Expression&>(e).push_adjoint<Expression::num_actives, 0>(
        *node, 1.0);

    //  Set my node
    node_ = node;
  }

  //  The value and node for this aad_double, same as traditional
  double value_{};
  node* node_{};
};
}  // namespace aad