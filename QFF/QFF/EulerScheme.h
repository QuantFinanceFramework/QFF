#pragma once
#include "IDiscretisationScheme.h"

class EulerScheme :
	public IDiscretisationScheme
{
public:
	EulerScheme() = default;
	~EulerScheme() = default;

	double evolve(double mu, double sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const override;

private:
	double drift(double mu, double previousValue, double previousTime, double timeStep) const;
	double diffusion(double sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const;
};

