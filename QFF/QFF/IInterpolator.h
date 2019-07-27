#pragma once
#include <map>
#include <memory>

namespace qff {
using std::map;
using std::unique_ptr;

class IInterpolator {
 public:
  IInterpolator() = default;
  virtual ~IInterpolator() = default;

  virtual unique_ptr<IInterpolator> Clone() const = 0;

  virtual double Interpol(const double& query_time,
                          const map<double, double>& data) const = 0;
};
}  // namespace qff
