#include "SobolNormalRsg.h"
#include "BeasleySpringerMoroInverseNormalCDF.h"

namespace qff {
	SobolNormalRsg::SobolNormalRsg(size_t dimension) :
		m_dimension{ dimension },
		m_engine{ dimension },
		m_generator{ m_engine, boost::random::uniform_01<double>() }{}

	vector<double> SobolNormalRsg::generateNormalSequence()
	{
		vector<double> result(m_dimension);
		std::generate(result.begin(), result.end(), m_generator);
		std::transform(result.begin(), result.end(), result.begin(), inverseCumulativeNormal);

		return result;
	}

	void SobolNormalRsg::setDimension(size_t dimension)
	{
		m_dimension = dimension;
		m_engine = boost::random::sobol{ dimension };
	}
}
