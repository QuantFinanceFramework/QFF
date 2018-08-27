#include "PseudoNormalRsg.h"

PseudoNormalRsg::PseudoNormalRsg(int dimension, unsigned int seed) :m_dimension{ dimension }, m_rng { std::mt19937{ seed } }, m_dist{ std::normal_distribution<double>{0,1} } {}

vector<double> PseudoNormalRsg::generateNormalSequence()
{
	vector<double> result;
	for (int i = 0; i < m_dimension; i++) 
	{
		result.emplace_back(m_dist(m_rng));
	}
	return result;
}
