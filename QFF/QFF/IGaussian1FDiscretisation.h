#pragma once
#include "IParameter.h"

class IGaussian1FDiscretisation
{
public:
	IGaussian1FDiscretisation() = default;
	virtual ~IGaussian1FDiscretisation() = default;

	virtual double evolve(const IParameter& kappa, const IParameter& sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const = 0;
};
