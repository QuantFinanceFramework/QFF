#pragma once
#include "IBlackScholesDiscretisation.h"

class BlackScholesEulerScheme :
	public IBlackScholesDiscretisation
{
public:
	BlackScholesEulerScheme() = default;
	~BlackScholesEulerScheme() = default;

	double evolve(const IParameter& mu, const IParameter& sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const override;

private:
	double drift(const IParameter& mu, double previousValue, double previousTime, double timeStep) const;
	double diffusion(const IParameter& sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const;
};

