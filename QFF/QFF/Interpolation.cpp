#include "Interpolation.h"
#include <cmath>

namespace qff {
double LinearInterpol(const double& query, const map<double, double>& data) {
  const auto position = data.find(query);
  if (position == data.end()) {
    const auto next = data.upper_bound(query);
    const auto previous = std::prev(next);
    if (next == data.end()) {
      return previous->second;
    }
    if (next == data.begin()) {
      return next->second;
    }

    const auto delta =
        (query - previous->first) / (next->first - previous->first);
    return delta * next->second + (1 - delta) * previous->second;
  }
  return position->second;
}

double LogLinearInterpol(const double& query, const map<double, double>& data) {
  const auto position = data.find(query);
  if (position == data.end()) {
    const auto next = data.upper_bound(query);
    const auto previous = std::prev(next);
    if (next == data.end()) {
      return previous->second;
    }
    if (next == data.begin()) {
      return next->second;
    }

    const auto delta =
        (query - previous->first) / (next->first - previous->first);
    return pow(next->second, delta) * pow(previous->second, 1-delta);
  }
  return position->second;
}

double LinearExtrapol(const double& query, const map<double, double>& data) {
  const auto last = std::prev(data.upper_bound(query));
  const auto second_last = std::prev(last);
  return last->second + (last->second - second_last->second) /
                            (last->first - second_last->first) *
                            (query - last->first);
}

double LogLinearExtrapol(const double& query, const map<double, double>& data) {
  const auto last = std::prev(data.upper_bound(query));
  const auto second_last = std::prev(last);
  const auto delta =
      (query - second_last->first) / (last->first - second_last->first);
  return pow(last->second, delta) * pow(second_last->second, 1 - delta);
}

double ConstantExtrapol(const double& query, const map<double, double>& data) {
  return std::prev(data.end())->second;
}
}  // namespace qff