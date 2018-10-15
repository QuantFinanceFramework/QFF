#include "PseudoNormalRsg.h"
#include <functional>

PseudoNormalRsg::PseudoNormalRsg(size_t dimension, unsigned int seed) : m_dimension{ dimension }, m_rng { std::mt19937{ seed } }, m_dist{ std::normal_distribution<double>{0,1} } {}

PseudoNormalRsg::PseudoNormalRsg(size_t dimension) : m_dimension{ dimension }, m_rng{ std::mt19937{std::random_device{}()} } {}

vector<double> PseudoNormalRsg::generateNormalSequence()
{
	vector<double> result(m_dimension);
	std::generate(result.begin(), result.end(), std::bind(m_dist, m_rng));

	return result;
}
