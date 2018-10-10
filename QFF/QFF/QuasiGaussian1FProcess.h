#pragma once
#include "IStochasticProcess.h"
#include "IQuasiGaussian1FDiscretisation.h"
#include "IParameter.h"
#include <memory>

using std::shared_ptr;

class QuasiGaussian1FProcess :
	public IStochasticProcess
{
public:
	QuasiGaussian1FProcess() = default;
	QuasiGaussian1FProcess(shared_ptr<IParameter> kappa, shared_ptr<IParameter> sigma, shared_ptr<IParameter> beta, shared_ptr<IParameter> s0, shared_ptr<IQuasiGaussian1FDiscretisation> discretisation);

	~QuasiGaussian1FProcess() = default;

	vector<double> evolve(vector<double> previousValue, double previousTime, double timeStep, vector<double> randomNormal) const override;

private:
	shared_ptr<IParameter> m_kappa;
	shared_ptr<IParameter> m_sigma;
	shared_ptr<IParameter> m_beta;
	shared_ptr<IParameter> m_s0;
	shared_ptr<IQuasiGaussian1FDiscretisation> m_discretisation;
};

