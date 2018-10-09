#include "Gaussian1FEulerScheme.h"
#include <cmath>

double Gaussian1FEulerScheme::evolve(const IParameter& kappa, const IParameter& sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const
{
	return previousValue + drift(kappa, sigma, previousValue, previousTime, timeStep) + diffusion(sigma, previousValue, previousTime, timeStep, randomNormal);
}

double Gaussian1FEulerScheme::drift(const IParameter& kappa, const IParameter& sigma, double previousValue, double previousTime, double timeStep) const
{
	return (y(kappa, sigma, previousTime) - kappa[previousTime] * previousValue) * timeStep;
}

double Gaussian1FEulerScheme::diffusion(const IParameter& sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const
{
	return sigma[previousTime] * sqrt(timeStep) * randomNormal;
}

double Gaussian1FEulerScheme::y(const IParameter& kappa, const IParameter& sigma, double previousTime) const
{
	auto kappaIntegral = kappa.integral(0.0, previousTime);
	auto sigmaIntegralSquare = sigma.integralSquare(0.0, previousTime);
	return exp(-2 * kappaIntegral * sigmaIntegralSquare);
}
