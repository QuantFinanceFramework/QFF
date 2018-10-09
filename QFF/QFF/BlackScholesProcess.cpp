#include "BlackScholesProcess.h"

BlackScholesProcess::BlackScholesProcess(shared_ptr<IParameter> mu, shared_ptr<IParameter> sigma, shared_ptr<IBlackScholesDiscretisation> discretisation) : m_mu{ mu }, m_sigma{ sigma }, m_discretisation{ discretisation } {}

double BlackScholesProcess::evolve(double previousValue, double previousTime, double timeStep, double randomNormal) const
{
	return m_discretisation->evolve(*m_mu, *m_sigma, previousValue, previousTime, timeStep, randomNormal);
}
