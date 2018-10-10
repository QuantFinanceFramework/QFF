#include "QuasiGaussian1FProcess.h"

QuasiGaussian1FProcess::QuasiGaussian1FProcess(
	shared_ptr<IParameter> kappa, 
	shared_ptr<IParameter> sigma, 
	shared_ptr<IParameter> beta, 
	shared_ptr<IParameter> s0, 
	shared_ptr<IQuasiGaussian1FDiscretisation> discretisation)
	:m_kappa{ kappa }, m_sigma{ sigma }, m_beta{ beta }, m_s0{ s0 }, m_discretisation{ discretisation }{}

vector<double> QuasiGaussian1FProcess::evolve(vector<double> previousValue, double previousTime, double timeStep, vector<double> randomNormal) const
{
	return m_discretisation->evolve(*m_kappa, *m_sigma, *m_beta, *m_s0, previousValue, previousTime, timeStep, randomNormal[0]);
}
