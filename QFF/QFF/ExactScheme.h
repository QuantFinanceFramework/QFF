#pragma once
#include "IDiscretisationScheme.h"
class ExactScheme :
	public IDiscretisationScheme
{
public:
	ExactScheme() = default;
	~ExactScheme() = default;

	double evolve(double mu, double sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const override;
};

