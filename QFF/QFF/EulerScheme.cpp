#include "EulerScheme.h"

double EulerScheme::evolve(double mu, double sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const
{
	return previousValue + drift(mu, previousValue, previousTime, timeStep) + diffusion(sigma, previousValue, previousTime, timeStep, randomNormal);
}

double EulerScheme::drift(double mu, double previousValue, double previousTime, double timeStep) const
{
	return mu * previousValue * timeStep;
}

double EulerScheme::diffusion(double sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const
{
	return sigma * previousValue * sqrt(timeStep) * randomNormal;
}


