#include "BlackScholesEulerScheme.h"
#include <cmath>

double BlackScholesEulerScheme::evolve(const IParameter& mu, const IParameter& sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const
{
	return previousValue + drift(mu, previousValue, previousTime, timeStep) + diffusion(sigma, previousValue, previousTime, timeStep, randomNormal);
}

double BlackScholesEulerScheme::drift(const IParameter& mu, double previousValue, double previousTime, double timeStep) const
{
	return mu[previousTime] * previousValue * timeStep;
}

double BlackScholesEulerScheme::diffusion(const IParameter& sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const
{
	return sigma[previousTime] * previousValue * sqrt(timeStep) * randomNormal;
}


