#include "Gaussian1FProcess.h"

Gaussian1FProcess::Gaussian1FProcess(shared_ptr<IParameter> kappa, shared_ptr<IParameter> sigma, shared_ptr<IGaussian1FDiscretisation> discretisation) : m_kappa{ kappa }, m_sigma{ sigma }, m_discretisation{ discretisation }{}

double Gaussian1FProcess::evolve(double previousValue, double previousTime, double timeStep, double randomNormal) const
{
	return m_discretisation->evolve(*m_kappa, *m_sigma, previousValue, previousTime, timeStep, randomNormal);
}
