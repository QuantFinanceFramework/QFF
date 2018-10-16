#include "QuasiGaussianShortRate1FProcess.h"
#include <cmath>

using std::move;

QuasiGaussianShortRate1FProcess::QuasiGaussianShortRate1FProcess(
	unique_ptr<ConstantParameter> kappa,
	unique_ptr<IParameter> lamda_r,
	unique_ptr<IParameter> beta_r,
	unique_ptr<IParameter> alpha_r,
	unique_ptr<IDiscretisation> discretisation)
	:m_kappa{ move(kappa) }, m_lamda_r{ move(lamda_r) }, m_beta_r{ move(beta_r) }, m_alpha_r{ move(alpha_r) }, m_discretisation{ move(discretisation) }{}

vector<double> QuasiGaussianShortRate1FProcess::evolve(vector<double> previousValues, double previousTime, double timeStep, vector<double> randomNormal) const
{
	return m_discretisation->next(*this, previousValues, previousTime, timeStep, randomNormal[0]);
}

double QuasiGaussianShortRate1FProcess::xDrift(double time, double x, double y) const
{
	return (y - m_kappa->operator[](time) * x);
}

double QuasiGaussianShortRate1FProcess::yDrift(double time,double x, double y) const
{
	return pow(xDiffusion(time, x), 2) - 2 * m_kappa->operator[](time) * y;
}

double QuasiGaussianShortRate1FProcess::xDiffusion(double time, double x) const
{
	return m_lamda_r->operator[](time) * (m_alpha_r->operator[](time) + m_beta_r->operator[](time) * x);
}

vector<double> QuasiGaussianShortRate1FProcess::EulerScheme::next(const QuasiGaussianShortRate1FProcess & process, vector<double> previousValues, double previousTime, double timeStep, double randomNormal) const
{
	vector<double> result(2);
	auto x = previousValues[0];
	auto y = previousValues[1];

	result[0] = x + process.xDrift(previousTime, x, y) * timeStep + process.xDiffusion(previousTime, x) * sqrt(timeStep) * randomNormal;
	result[1] = y + process.yDrift(previousTime, x, y) * timeStep;

	return result;
}
