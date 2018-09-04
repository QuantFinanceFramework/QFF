#include "ExactScheme.h"

double ExactScheme::evolve(double mu, double sigma, double previousValues, double previousTime, double timeStep, double randomNormals) const
{
	return previousValues * exp((mu - 0.5 * sigma * sigma) * timeStep + sigma * sqrt(timeStep) * randomNormals);
}
