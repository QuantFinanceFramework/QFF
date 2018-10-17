#pragma once
#include "INormalRandomSequenceGenerator.h"
#include <random>

class PseudoNormalRsg :
	public INormalRandomSequenceGenerator
{
public:
	PseudoNormalRsg(size_t dimension, unsigned int seed);
	PseudoNormalRsg(size_t dimension);
	~PseudoNormalRsg() = default;

	vector<double> generateNormalSequence() override;
	void setDimension(size_t dimension) override;

private:
	size_t m_dimension;
	std::mt19937 m_rng;
	std::normal_distribution<double> m_dist;
};
