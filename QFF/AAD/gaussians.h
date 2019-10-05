#pragma once
#include <cmath>
namespace aad {
constexpr auto eps = 1.0e-08;

inline auto normal_dens(const double x) {
  return x < -10.0 || 10.0 < x ? 0.0 : std::exp(-0.5 * x * x) / 2.506628274631;
}

inline auto normal_cdf(const double x) {
  if (x < -10.0) return 0.0;
  if (x > 10.0) return 1.0;
  if (x < 0.0) return 1.0 - normal_cdf(-x);

  static constexpr auto p = 0.2316419;
  static constexpr auto b1 = 0.319381530;
  static constexpr auto b2 = -0.356563782;
  static constexpr auto b3 = 1.781477937;
  static constexpr auto b4 = -1.821255978;
  static constexpr auto b5 = 1.330274429;

  const auto t = 1.0 / (1.0 + p * x);

  const auto pol = t * (b1 + t * (b2 + t * (b3 + t * (b4 + t * b5))));

  const auto pdf = normal_dens(x);

  return 1.0 - pdf * pol;
}

inline auto inv_normal_cdf(const double p) {
  const auto sup = p > 0.5;
  const auto up = sup ? 1.0 - p : p;

  static constexpr auto a0 = 2.50662823884;
  static constexpr auto a1 = -18.61500062529;
  static constexpr auto a2 = 41.39119773534;
  static constexpr auto a3 = -25.44106049637;

  static constexpr auto b0 = -8.47351093090;
  static constexpr auto b1 = 23.08336743743;
  static constexpr auto b2 = -21.06224101826;
  static constexpr auto b3 = 3.13082909833;

  static constexpr auto c0 = 0.3374754822726147;
  static constexpr auto c1 = 0.9761690190917186;
  static constexpr auto c2 = 0.1607979714918209;
  static constexpr auto c3 = 0.0276438810333863;
  static constexpr auto c4 = 0.0038405729373609;
  static constexpr auto c5 = 0.0003951896511919;
  static constexpr auto c6 = 0.0000321767881768;
  static constexpr auto c7 = 0.0000002888167364;
  static constexpr auto c8 = 0.0000003960315187;

  const auto x = up - 0.5;
  double r;

  if (std::fabs(x) < 0.42) {
    r = x * x;
    r = x * (((a3 * r + a2) * r + a1) * r + a0) /
        ((((b3 * r + b2) * r + b1) * r + b0) * r + 1.0);
    return sup ? -r : r;
  }

  r = up;
  r = std::log(-std::log(r));
  r = c0 +
      r * (c1 +
           r * (c2 +
                r * (c3 + r * (c4 + r * (c5 + r * (c6 + r * (c7 + r * c8)))))));

  return sup ? r : -r;
}
}  // namespace aad