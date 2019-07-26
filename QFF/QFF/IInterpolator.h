#pragma once
#include <map>

namespace qff {
using std::map;

class IInterpolator {
 public:
  IInterpolator() = default;
  virtual ~IInterpolator() = default;

  virtual double Interpol(const double& query_time,
                          const map<double, double>& data) const = 0;
};
}  // namespace qff
