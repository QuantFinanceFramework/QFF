#include "PiecewiseConstantParameter.h"
#include <cmath>
#include <utility>

namespace qff {
PiecewiseConstantParameter::PiecewiseConstantParameter(
	map<double, double> value)
    : value_{std::move(value)} {}

double PiecewiseConstantParameter::operator[](double time) const {
  if (time < value_.begin()->first) return 0.0;
  return std::prev(value_.upper_bound(time))->second;
}

double PiecewiseConstantParameter::Integral(double time1, double time2) const {
  if (time1 < value_.begin()->first || time2 < value_.begin()->first)
    return 0.0;

  auto end_time = 0.0;
  auto start_time = time1;
  auto result = 0.0;

  for (auto iter = prev(value_.upper_bound(time1));
       iter != value_.upper_bound(time2); ++iter) {
    if (next(iter) == value_.upper_bound(time2))
      end_time = time2;
    else
      end_time = next(iter)->first;

    result += iter->second * (end_time - start_time);
    start_time = end_time;
  }

  return result;
}

double PiecewiseConstantParameter::IntegralSquare(double time1,
                                                  double time2) const {
  if (time1 < value_.begin()->first || time2 < value_.begin()->first)
    return 0.0;

  auto end_time = 0.0;
  auto start_time = time1;
  auto result = 0.0;

  for (auto iter = prev(value_.upper_bound(time1));
       iter != value_.upper_bound(time2); ++iter) {
    if (next(iter) == value_.upper_bound(time2))
      end_time = time2;
    else
      end_time = next(iter)->first;

    result += std::pow(iter->second, 2) * (end_time - start_time);
    start_time = end_time;
  }

  return result;
}
}  // namespace qff