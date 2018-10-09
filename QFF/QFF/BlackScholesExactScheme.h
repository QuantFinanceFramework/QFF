#pragma once
#include "IBlackScholesDiscretisation.h"

class BlackScholesExactScheme :
	public IBlackScholesDiscretisation
{
public:
	BlackScholesExactScheme() = default;
	~BlackScholesExactScheme() = default;

	double evolve(const IParameter& mu, const IParameter& sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const override;
};

