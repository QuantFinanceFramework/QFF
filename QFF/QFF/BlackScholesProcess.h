#pragma once
#include "IStochastic1FProcess.h"
#include "IBlackScholesDiscretisation.h"
#include "IParameter.h"
#include <memory>

using std::shared_ptr;

class BlackScholesProcess :
	public IStochastic1FProcess
{
public:
	BlackScholesProcess() = default;
	BlackScholesProcess(shared_ptr<IParameter> mu, shared_ptr<IParameter> sigma, shared_ptr<IBlackScholesDiscretisation> discretisation);
	~BlackScholesProcess() = default;

	double evolve(double previousValue, double previousTime, double timeStep, double randomNormal) const override;

private:
	shared_ptr<IParameter> m_mu;
	shared_ptr<IParameter> m_sigma;
	shared_ptr<IBlackScholesDiscretisation> m_discretisation;
};

