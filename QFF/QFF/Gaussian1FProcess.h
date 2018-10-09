#pragma once
#include "IStochastic1FProcess.h"
#include "IGaussian1FDiscretisation.h"
#include "IParameter.h"
#include <memory>

using std::shared_ptr;

class Gaussian1FProcess :
	public IStochastic1FProcess
{
public:
	Gaussian1FProcess() = default;
	Gaussian1FProcess(shared_ptr<IParameter> kappa, shared_ptr<IParameter> sigma, shared_ptr<IGaussian1FDiscretisation> discretisation);
	~Gaussian1FProcess() = default;

	double evolve(double previousValue, double previousTime, double timeStep, double randomNormal) const override;

private:
	shared_ptr<IParameter> m_kappa;
	shared_ptr<IParameter> m_sigma;
	shared_ptr<IGaussian1FDiscretisation> m_discretisation;
};

