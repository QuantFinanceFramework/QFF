#pragma once
#include <boost/random/sobol.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/variate_generator.hpp>
#include "INormalRandomSequenceGenerator.h"

namespace qff {
class SobolNormalRsg : public INormalRandomSequenceGenerator {
  using sobol_generator =
      boost::variate_generator<boost::random::sobol&,
                               boost::random::uniform_01<double>>;

 public:
  SobolNormalRsg() = default;
  explicit SobolNormalRsg(size_t dimension);

  std::vector<double> GenerateNormalSequence() override;
  void SetDimension(size_t dimension) override;

 private:
  size_t dimension_;
  boost::random::sobol engine_;
  sobol_generator generator_;
};
}  // namespace qff
