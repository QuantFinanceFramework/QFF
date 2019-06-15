#include "BlackScholesProcess.h"
#include <cmath>

using std::move;

BlackScholesProcess::BlackScholesProcess(unique_ptr<IParameter> mu, unique_ptr<IParameter> sigma, unique_ptr<IDiscretisation> discretisation) : m_mu{ move(mu) }, m_sigma{ move(sigma) }, m_discretisation{ move(discretisation) } {}

double BlackScholesProcess::evolve(double previousValue, double previousTime, double timeStep, double randomNormal) const
{
	return m_discretisation->next(*this, previousValue, previousTime, timeStep, randomNormal);
}

size_t BlackScholesProcess::dimension() const
{
	return 1;
}

double BlackScholesProcess::drift(double time, double s) const
{
	return m_mu->operator[](time) * s;
}

double BlackScholesProcess::diffusion(double time, double s) const
{
	return m_sigma->operator[](time) * s;
}

double BlackScholesProcess::ExactScheme::next(const BlackScholesProcess & process, double previousValue, double previousTime, double timeStep, double randomNormal) const
{
	auto muAvg = process.m_mu->mean(previousTime, previousTime + timeStep);
	auto sigmaAvg = process.m_sigma->rootMeanSquare(previousTime, previousTime + timeStep);
	return previousValue * exp((muAvg - 0.5 * sigmaAvg * sigmaAvg) * timeStep + sigmaAvg * sqrt(timeStep) * randomNormal);
}

double BlackScholesProcess::EulerScheme::next(const BlackScholesProcess & process, double previousValue, double previousTime, double timeStep, double randomNormal) const
{
	return previousValue + process.drift(previousTime, previousValue) * timeStep + process.diffusion(previousTime, previousValue) * sqrt(timeStep) * randomNormal;
}
