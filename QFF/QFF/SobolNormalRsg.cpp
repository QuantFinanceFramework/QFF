#include "SobolNormalRsg.h"
#include "BeasleySpringerMoroInverseNormalCDF.h"

using std::vector;

namespace qff {
SobolNormalRsg::SobolNormalRsg(size_t dimension)
    : dimension_{dimension},
      engine_{dimension},
      generator_{engine_, boost::random::uniform_01<double>()} {}

vector<double> SobolNormalRsg::GenerateNormalSequence() {
  vector<double> result(dimension_);
  std::generate(result.begin(), result.end(), generator_);
  std::transform(result.begin(), result.end(), result.begin(),
                 InverseCumulativeNormal);

  return result;
}

void SobolNormalRsg::SetDimension(size_t dimension) {
  dimension_ = dimension;
  engine_ = boost::random::sobol{dimension};
}
}  // namespace qff
