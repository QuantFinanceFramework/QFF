#pragma once
#include "INormalRandomSequenceGenerator.h"
#include <random>

class PseudoNormalRsg :
	public INormalRandomSequenceGenerator
{
public:
	PseudoNormalRsg(int dimension, unsigned int seed);
	~PseudoNormalRsg() = default;

	vector<double> generateNormalSequence() override;

private:
	int m_dimension;
	std::mt19937 m_rng;
	std::normal_distribution<double> m_dist;
};
