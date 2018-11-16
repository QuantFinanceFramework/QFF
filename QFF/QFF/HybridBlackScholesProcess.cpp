#include "HybridBlackScholesProcess.h"
#include <cmath>
#include <algorithm>

using std::move;

HybridBlackScholesProcess::HybridBlackScholesProcess(
	unique_ptr<IStochasticShortRateProcess> domesticSRProcess,
	unique_ptr<IStochasticShortRateProcess> foreignSRProcess,
	unique_ptr<IParameter> sigma, 
	unique_ptr<IDiscretisation> discretisation,
	const vector<vector<double>>& correlationMatrix):
	m_domesticSRProcess{ move(domesticSRProcess) },
	m_foreignSRProcess{ move(foreignSRProcess) },
	m_sigma{ move(sigma) },
	m_discretisation{ move(discretisation) },
	m_correlationMatrix{ correlationMatrix }{}

vector<double> HybridBlackScholesProcess::evolve(
	const vector<double> & previousValue, 
	double previousTime, 
	double timeStep, 
	const vector<double> & randomNormal) const
{
	return m_discretisation->next(*this, previousValue, previousTime, timeStep, randomNormal);
}

size_t HybridBlackScholesProcess::factors() const
{
	return m_domesticSRProcess->factors() + m_foreignSRProcess->factors() + 1;
}

size_t HybridBlackScholesProcess::dimension() const
{
	return m_domesticSRProcess->dimension() + m_foreignSRProcess->dimension();
}

double HybridBlackScholesProcess::diffusion(double time, double s) const
{
	return m_sigma->operator[](time) * s;
}

vector<double> HybridBlackScholesProcess::ExactScheme::next(
	const HybridBlackScholesProcess & process,
	const vector<double> & previousValue,
	double previousTime,
	double timeStep,
	const vector<double> & randomNormal) const
{
	auto rDDimension = process.m_domesticSRProcess->dimension();
	auto rFDimension = process.m_foreignSRProcess->dimension();
	auto rDFactors = process.m_domesticSRProcess->factors();
	auto rFFactors = process.m_foreignSRProcess->factors();
	vector<double> rDState{ previousValue.begin(), previousValue.begin() + rDDimension };
	vector<double> rFState{ previousValue.begin() + rDDimension + 1, previousValue.begin() + rDDimension + 1 + rFDimension };
	auto rDStateNext = process.m_domesticSRProcess->evolve(rDState, previousTime, timeStep, { randomNormal.begin(), randomNormal.begin() + rDFactors });
	auto rFStateNext = process.m_foreignSRProcess->evolve(rFState, previousTime, timeStep, { randomNormal.begin() + rDFactors + 1, randomNormal.begin() + rDFactors + 1 + rFFactors });
	auto sigmaAvg = process.m_sigma->rootMeanSquare(previousTime, previousTime + timeStep);
	auto rDBond = process.m_domesticSRProcess->zeroCouponBondPrice(previousTime, previousTime + timeStep, rDStateNext);
	auto rFBond = process.m_foreignSRProcess->zeroCouponBondPrice(previousTime, previousTime + timeStep, rFStateNext);
	auto currentValue = previousValue.back() * rDBond/ rFBond * exp(- 0.5 * sigmaAvg * sigmaAvg) * timeStep + sigmaAvg * sqrt(timeStep) * randomNormal.back();
	vector<double> result;
	std::merge(rDStateNext.begin(), rDStateNext.end(), rFStateNext.begin(), rFStateNext.end(), result.begin());
	result.push_back(currentValue);
	return result;
}
