#pragma once
#include "IDayCounter.h"
#include "IInterestRateCurve.h"
#include "IInterpolator.h"

namespace qff {
class ZeroRateCurve final : public IInterestRateCurve {
 public:
  ZeroRateCurve() = default;

  ZeroRateCurve(boost::gregorian::date curve_date,
                std::vector<boost::gregorian::date> dates,
                const std::vector<double>& zero_rates,
                const IInterpolator& interpolator,
                const IDayCounter& day_counter);

  ZeroRateCurve(boost::gregorian::date&& curve_date,
                std::vector<boost::gregorian::date>&& dates,
                std::map<double, double>&& zero_rates_map,
                std::unique_ptr<IInterpolator> interpolator,
                std::unique_ptr<IDayCounter> day_counter);

  boost::gregorian::date GetCurveDate() const;

  double GetDiscountFactor(
      const boost::gregorian::date& query_date) const override;
  double GetDiscountFactor(double query_time) const override;

  double GetForwardRate(const boost::gregorian::date& start_date,
                        const boost::gregorian::date& end_date) const override;
  double GetForwardRate(double start_time, double end_time) const override;

  double GetZeroRate(const boost::gregorian::date& query_date) const override;
  double GetZeroRate(double query_time) const override;

 private:
  boost::gregorian::date curve_date_;
  std::vector<boost::gregorian::date> dates_;
  std::map<double, double> zero_rates_map_;
  std::unique_ptr<IInterpolator> interpolator_;
  std::unique_ptr<IDayCounter> day_counter_;
};
}  // namespace qff