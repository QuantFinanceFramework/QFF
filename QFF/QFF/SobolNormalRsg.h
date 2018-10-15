#pragma once
#include "INormalRandomSequenceGenerator.h"
#include <boost/random/sobol.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>

class SobolNormalRsg :
	public INormalRandomSequenceGenerator
{
	using sobol_generator = boost::variate_generator<boost::random::sobol&, boost::random::normal_distribution<double>>;

public:
	SobolNormalRsg() = default;
	SobolNormalRsg(size_t dimension);
	~SobolNormalRsg() = default;

	vector<double> generateNormalSequence() override;

private:
	size_t m_dimension;
	boost::random::sobol m_engine;
	sobol_generator m_generator;

};

