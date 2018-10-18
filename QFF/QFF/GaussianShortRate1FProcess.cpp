#include "GaussianShortRate1FProcess.h"

using std::move;

GaussianShortRate1FProcess::GaussianShortRate1FProcess(
	shared_ptr<DiscountCurve> disCurve, 
	unique_ptr<ConstantParameter> kappa, 
	unique_ptr<IParameter> sigma, 
	unique_ptr<IDiscretisation> discretisation) : 
	m_disCurve{ disCurve }, 
	m_kappa { move(kappa) }, 
	m_sigma{ move(sigma) }, 
	m_discretisation{ move(discretisation) }{}

double GaussianShortRate1FProcess::evolve(double previousValue, double previousTime, double timeStep, double randomNormal) const
{
	return m_discretisation->next(*this, previousValue, previousTime, timeStep, randomNormal);
}

double GaussianShortRate1FProcess::zeroCouponBondPrice(double t, double T, double x) const
{
	auto gValue = g(t, T);
	return m_disCurve->getDiscountFactor(T) / m_disCurve->getDiscountFactor(t) * exp(-x * gValue -0.5 * y(t) * gValue * gValue);
}

double GaussianShortRate1FProcess::drift(double time, double x) const
{
	return (y(time) - m_kappa->operator[](time) * x);
}

double GaussianShortRate1FProcess::diffusion(double time) const
{
	return m_sigma->operator[](time);
}

double GaussianShortRate1FProcess::y(double time) const
{
	return exp(-2 * m_kappa->integral(0.0, time) * m_sigma->integralSquare(0.0, time));
}

double GaussianShortRate1FProcess::g(double t, double T) const
{
	auto kappa = m_kappa->operator[](0);
	return (1.0 - exp(-kappa *(T-t)))/ kappa;
}

double GaussianShortRate1FProcess::EulerScheme::next(const GaussianShortRate1FProcess & process, 
	double previousValue, 
	double previousTime, 
	double timeStep, 
	double randomNormal) const
{
	return previousValue + process.drift(previousTime, previousValue) * timeStep + process.diffusion(previousTime) * sqrt(timeStep) * randomNormal;
}
