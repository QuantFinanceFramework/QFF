#pragma once
#include <map>
#include <memory>

namespace qff {

class IInterpolator {
 public:
  IInterpolator() = default;
  virtual ~IInterpolator() = default;

  virtual std::unique_ptr<IInterpolator> Clone() const = 0;

  virtual double Interpol(const double& query_time,
                          const std::map<double, double>& data) const = 0;
};
}  // namespace qff
