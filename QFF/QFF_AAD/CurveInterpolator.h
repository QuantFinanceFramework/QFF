#pragma once
#include <functional>

#include "IInterpolator.h"
#include "Interpolation.h"

namespace qff_a {
template <typename T>
class CurveInterpolator : public IInterpolator<T> {
 public:
  CurveInterpolator() = default;

  CurveInterpolator(
      std::function<T(const double&, const std::map<double, T>&)> interpol_func,
      std::function<T(const double&, const std::map<double, T>&)>
          right_extrpol_func);

  T Interpol(const double& query_time,
             const std::map<double, T>& data) const override;

  std::unique_ptr<IInterpolator<T>> Clone() const override;

 private:
  std::function<T(const double&, const std::map<double, T>&)> interpol_func_ =
      LogLinearInterpol<T>;
  std::function<T(const double&, const std::map<double, T>&)>
      right_extrapol_func_ = LogLinearExtrapol<T>;
};

template <typename T>
CurveInterpolator<T>::CurveInterpolator(
    std::function<T(const double&, const std::map<double, T>&)> interpol_func,
    std::function<T(const double&, const std::map<double, T>&)>
        right_extrpol_func)
    : interpol_func_(interpol_func), right_extrapol_func_(right_extrpol_func) {}

template <typename T>
T CurveInterpolator<T>::Interpol(const double& query_time,
                                 const std::map<double, T>& data) const {
  if (query_time > std::prev(data.end())->first)
    return (right_extrapol_func_(query_time, data));
  return (interpol_func_(query_time, data));
}

template <typename T>
std::unique_ptr<IInterpolator<T>> CurveInterpolator<T>::Clone() const {
  return std::make_unique<CurveInterpolator<T>>(*this);
}
}  // namespace qff_a