#include "BlackScholesExactScheme.h"
#include <cmath>

double BlackScholesExactScheme::evolve(const IParameter& mu, const IParameter& sigma, double previousValues, double previousTime, double timeStep, double randomNormals) const
{
	auto muAvg = mu.mean(previousTime, previousTime + timeStep);
	auto sigmaAvg = sigma.rootMeanSquare(previousTime, previousTime + timeStep);
	return previousValues * exp((muAvg - 0.5 * sigmaAvg * sigmaAvg) * timeStep + sigmaAvg * sqrt(timeStep) * randomNormals);
}
