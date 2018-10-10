#include "QuasiGaussian1FEulerScheme.h"
#include <algorithm>
#include <cmath>

vector<double> QuasiGaussian1FEulerScheme::evolve(const IParameter& kappa, const IParameter& sigma, const IParameter& beta, const IParameter& s0, const vector <double>& previousValue, double previousTime, double timeStep, double randomNormal) const
{
	auto result = previousValue;

	auto driftValue = drift(kappa, sigma, beta, s0, previousValue, previousTime, timeStep);
	std::transform(result.begin(), result.end(), driftValue.begin(), result.begin(), std::plus<double>());

	auto diffusionValue = diffusion(sigma, beta, s0, previousValue, previousTime, timeStep, randomNormal);
	std::transform(result.begin(), result.end(), diffusionValue.begin(), result.begin(), std::plus<double>());

	return result;
}

vector<double> QuasiGaussian1FEulerScheme::drift(const IParameter & kappa, const IParameter & sigma, const IParameter & beta, const IParameter & s0, const vector<double>& previousValue, double previousTime, double timeStep) const
{
	vector<double> result{2};
	result[0] = (previousValue[1] - kappa[previousTime] * previousValue[0]) * timeStep;
	result[1] = (pow(sigmaR(sigma, beta, s0, previousValue, previousTime), 2) - 2 * kappa[previousTime] * previousValue[1]) * timeStep;

	return result;
}

vector<double> QuasiGaussian1FEulerScheme::diffusion(const IParameter & sigma, const IParameter & beta, const IParameter & s0, const vector<double>& previousValue, double previousTime, double timeStep, double randomNormal) const
{
	vector<double> result(2);
	result[0] = sigmaR(sigma, beta, s0, previousValue, previousTime) * sqrt(timeStep) * randomNormal;
	result[1] = 0.0;

	return result;
}

double QuasiGaussian1FEulerScheme::sigmaR(const IParameter & sigma, const IParameter & beta, const IParameter & s0, const vector<double>& previousValue, double previousTime) const
{
	return sigma[previousTime] * (beta[previousTime] * previousValue[0] + s0[previousTime]);
}
