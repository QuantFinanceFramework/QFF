#include "HybridBlackScholesProcess.h"
#include <cmath>

using std::move;

HybridBlackScholesProcess::HybridBlackScholesProcess(
	unique_ptr<IStochastic1FProcess> domesticSRProcess, 
	unique_ptr<IStochastic1FProcess> foreignSRProcess, 
	unique_ptr<IParameter> sigma, 
	unique_ptr<IDiscretisation> discretisation):
	m_domesticSRProcess{ move(domesticSRProcess) },
	m_foreignSRProcess{ move(foreignSRProcess) },
	m_sigma{ move(sigma) },
	m_discretisation{ move(discretisation) }{}

vector<double> HybridBlackScholesProcess::evolve(vector<double> previousValue, double previousTime, double timeStep, vector<double> randomNormal) const
{
	return m_discretisation->next(*this, previousValue, previousTime, timeStep, randomNormal);
}

size_t HybridBlackScholesProcess::numberOfFactors() const
{
	return m_domesticSRProcess->numberOfFactors() + m_foreignSRProcess->numberOfFactors() + 1;
}

double HybridBlackScholesProcess::diffusion(double time, double s) const
{
	return m_sigma->operator[](time) * s;
}

vector<double> HybridBlackScholesProcess::ExactScheme::next(const HybridBlackScholesProcess & process, vector<double> previousValue, double previousTime, double timeStep, vector<double> randomNormal) const
{
	auto rDomestic = process.m_domesticSRProcess->evolve(previousValue[0], previousTime, timeStep, randomNormal[0]);
	auto rForeign = process.m_foreignSRProcess->evolve(previousValue[1], previousTime, timeStep, randomNormal[1]);
	auto sigmaAvg = process.m_sigma->rootMeanSquare(previousTime, previousTime + timeStep);
	auto currentValue = previousValue[2] * exp((rDomestic - rForeign - 0.5 * sigmaAvg * sigmaAvg) * timeStep + sigmaAvg * sqrt(timeStep) * randomNormal[2]);
	return { rDomestic, rForeign, currentValue };
}

vector<double> HybridBlackScholesProcess::EulerScheme::next(const HybridBlackScholesProcess & process, vector<double> previousValue, double previousTime, double timeStep, vector<double> randomNormal) const
{
	auto rDomestic = process.m_domesticSRProcess->evolve(previousValue[0], previousTime, timeStep, randomNormal[0]);
	auto rForeign = process.m_foreignSRProcess->evolve(previousValue[1], previousTime, timeStep, randomNormal[1]);
	auto currentValue = previousValue[2] + (rDomestic + rForeign) * timeStep + process.diffusion(previousTime, previousValue[2]) * sqrt(timeStep) * randomNormal[2];
	return { rDomestic, rForeign, currentValue };
}
