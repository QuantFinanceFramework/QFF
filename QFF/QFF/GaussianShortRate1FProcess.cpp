#include "GaussianShortRate1FProcess.h"

using std::move;

GaussianShortRate1FProcess::GaussianShortRate1FProcess(
	shared_ptr<DiscountCurve> disCurve, 
	const vector<double> & term,
	const vector<double> & kappa,
	const vector<double> & sigma,
	unique_ptr<IDiscretisation> discretisation) : 
	m_disCurve{ disCurve },
	m_term { term },
	m_kappa { kappa }, 
	m_sigma{ sigma }, 
	m_discretisation{ move(discretisation) }{}

vector<double> GaussianShortRate1FProcess::evolve(
	const vector<double> & previousValue, 
	double previousTime, 
	double timeStep, 
	const vector<double> & randomNormal) const
{
	return vector<double> {m_discretisation->next(*this, previousValue[0], previousTime, timeStep, randomNormal[0])};
}

size_t GaussianShortRate1FProcess::factors() const
{
	return 1;
}

size_t GaussianShortRate1FProcess::dimension() const
{
	return 1;
}

double GaussianShortRate1FProcess::zeroCouponBondPrice(double t, double T, const vector<double> & state) const
{
	auto gValue = g(t, T);
	return m_disCurve->getDiscountFactor(T) / m_disCurve->getDiscountFactor(t) * exp(-state[0] * gValue -0.5 * y(t) * gValue * gValue);
}

double GaussianShortRate1FProcess::drift(double time, double x) const
{
	auto position = std::distance(m_term.begin(), std::prev(std::upper_bound(m_term.begin(), m_term.end(), time)));
	return (y(time) - m_kappa[position] * x);
}

double GaussianShortRate1FProcess::diffusion(double time) const
{
	auto position = std::distance(m_term.begin(), std::prev(std::upper_bound(m_term.begin(), m_term.end(), time)));
	return m_sigma[position];
}

double GaussianShortRate1FProcess::y(double time) const
{
	auto position = std::distance(m_term.begin(), std::prev(std::upper_bound(m_term.begin(), m_term.end(), time)));
	auto f = [&](size_t i) {return pow(m_sigma[i], 2) / (2 * m_kappa[i]) * (exp(-2 * m_kappa[i] * (time - m_term[i + 1])) - exp(-2 * m_kappa[i] * (time - m_term[i]))); };
	auto result = 0.0;
	for (size_t i = 0; i < position; ++i)
	{
		result += f(i);
	}
	if (m_term[position] == time) 
		return result;
	else 
		return result + pow(m_sigma[position], 2) / (2 * m_kappa[position]) * (1.0 - exp(-2 * m_kappa[position] * (time - m_term[position])));
}

double GaussianShortRate1FProcess::g(double t, double T) const
{
	return (1.0 - exp(-m_kappa[0] *(T-t)))/ m_kappa[0];
}

double GaussianShortRate1FProcess::EulerScheme::next(
	const GaussianShortRate1FProcess & process, 
	double previousValue, 
	double previousTime, 
	double timeStep, 
	double randomNormal) const
{
	return previousValue + process.drift(previousTime, previousValue) * timeStep + process.diffusion(previousTime) * sqrt(timeStep) * randomNormal;
}
