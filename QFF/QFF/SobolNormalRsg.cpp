#include "SobolNormalRsg.h"

SobolNormalRsg::SobolNormalRsg(size_t dimension) : 
	m_dimension{ dimension }, 
	m_engine{ dimension }, 
	m_generator{ m_engine, boost::random::normal_distribution<double>() }{}

vector<double> SobolNormalRsg::generateNormalSequence()
{
	vector<double> result(m_dimension);
	std::generate(result.begin(), result.end(), m_generator);

	return result;
}

