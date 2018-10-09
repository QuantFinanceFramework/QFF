#pragma once
#include "IParameter.h"

class IBlackScholesDiscretisation
{
public:
	IBlackScholesDiscretisation() = default;
	virtual ~IBlackScholesDiscretisation() = default;

	virtual double evolve(const IParameter& mu, const IParameter& sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const = 0;
};


