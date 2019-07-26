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
  SobolNormalRsg(size_t dimension);
  ~SobolNormalRsg() = default;

  vector<double> GenerateNormalSequence() override;
  void SetDimension(size_t dimension) override;

 private:
  size_t m_dimension;
  boost::random::sobol m_engine;
  sobol_generator m_generator;
};
}  // namespace qff
