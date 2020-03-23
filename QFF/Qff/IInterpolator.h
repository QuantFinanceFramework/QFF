#pragma once
#include <map>
#include <memory>

namespace qff_a {

template <typename T>
class IInterpolator {
 public:
  virtual ~IInterpolator() = default;

  virtual std::unique_ptr<IInterpolator> Clone() const = 0;

  virtual T Interpol(const double& query_time,
                     const std::map<double, T>& data) const = 0;
};
}  // namespace qff_a
