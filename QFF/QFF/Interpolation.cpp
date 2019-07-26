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
    return exp(delta * log(next->second) + (1 - delta) * log(previous->second));
  }
  return position->second;
}
}  // namespace qff