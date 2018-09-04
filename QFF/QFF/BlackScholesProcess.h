#pragma once
#include "IStochasticProcess.h"
#include "IDiscretisationScheme.h"
#include <memory>

using std::shared_ptr;
using std::make_shared;

class BlackScholesProcess :
	public IStochasticProcess
{
public:
	BlackScholesProcess() = delete;
	BlackScholesProcess(double mu, double sigma, shared_ptr<IDiscretisationScheme> discretisation);
	~BlackScholesProcess() = default;

	double evolve(double previousValue, double previousTime, double timeStep, double randomNormal) const override;

private:
	double m_mu;
	double m_sigma;
	shared_ptr<IDiscretisationScheme> m_discretisation;
};

