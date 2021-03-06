#pragma once
#include <map>

namespace qff_a {

template <typename T>
T LinearInterpol(const double& query, const std::map<double, T>& data) {
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
    return T(delta * next->second + (1 - delta) * previous->second);
  }
  return position->second;
}

template <typename T>
T LogLinearInterpol(const double& query, const std::map<double, T>& data) {
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
    return T(pow(next->second, delta) * pow(previous->second, 1 - delta));
  }
  return position->second;
}

template <typename T>
T ProductLinearInterpol(const double& query, const std::map<double, T>& data) {
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
    return T((delta * next->second * next->first +
              (1 - delta) * previous->second * previous->first) /
             query);
  }
  return position->second;
}

template <typename T>
T LinearExtrapol(const double& query, const std::map<double, T>& data) {
  const auto last = std::prev(data.upper_bound(query));
  const auto second_last = std::prev(last);
  return T(last->second + (last->second - second_last->second) /
                              (last->first - second_last->first) *
                              (query - last->first));
}

template <typename T>
T LogLinearExtrapol(const double& query, const std::map<double, T>& data) {
  const auto last = std::prev(data.upper_bound(query));
  const auto second_last = std::prev(last);
  const auto delta =
      (query - second_last->first) / (last->first - second_last->first);
  return T(pow(last->second, delta) * pow(second_last->second, 1 - delta));
}

template <typename T>
T ProductLinearExtrapol(const double& query, const std::map<double, T>& data) {
  const auto last = std::prev(data.upper_bound(query));
  const auto second_last = std::prev(last);
  return T((last->second * last->first +
           (last->second * last->first - second_last->second * second_last->first) /
                              (last->first - second_last->first) *
                              (query - last->first))/query);
}

template <typename T>
T ConstantExtrapol(const double& query, const std::map<double, T>& data) {
  return std::prev(data.end())->second;
}
}  // namespace qff_a