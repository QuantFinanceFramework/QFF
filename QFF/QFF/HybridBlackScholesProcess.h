#pragma once
#include "IStochasticProcess.h"
#include "IStochastic1FProcess.h"
#include "IParameter.h"
#include <memory>

using std::unique_ptr;

class HybridBlackScholesProcess :
	public IStochasticProcess
{
public:
	class IDiscretisation;
	class ExactScheme;
	class EulerScheme;

	HybridBlackScholesProcess() = default;
	HybridBlackScholesProcess(unique_ptr<IStochastic1FProcess> domesticSRProcess, unique_ptr<IStochastic1FProcess> foreignSRProcess, unique_ptr<IParameter> sigma, unique_ptr<IDiscretisation> discretisation);
	~HybridBlackScholesProcess() = default;

	vector<double> evolve(vector<double> previousValue, double previousTime, double timeStep, vector<double> randomNormal) const override;
	size_t numberOfFactors() const override;

private:
	unique_ptr<IStochastic1FProcess> m_domesticSRProcess;
	unique_ptr<IStochastic1FProcess> m_foreignSRProcess;
	unique_ptr<IParameter> m_sigma;
	unique_ptr<IDiscretisation> m_discretisation;
	double drift(double time, double s) const;
	double diffusion(double time, double s) const;
};

class HybridBlackScholesProcess::IDiscretisation
{
public:
	IDiscretisation() = default;
	virtual ~IDiscretisation() = default;

	virtual vector<double> next(const HybridBlackScholesProcess& process, vector<double> previousValue, double previousTime, double timeStep, vector<double> randomNormal) const = 0;
};

class HybridBlackScholesProcess::ExactScheme : public HybridBlackScholesProcess::IDiscretisation
{
public:
	ExactScheme() = default;
	virtual ~ExactScheme() = default;

	vector<double> next(const HybridBlackScholesProcess& process, vector<double> previousValue, double previousTime, double timeStep, vector<double> randomNormal) const override;
};

class HybridBlackScholesProcess::EulerScheme : public HybridBlackScholesProcess::IDiscretisation
{
public:
	EulerScheme() = default;
	virtual ~EulerScheme() = default;

	vector<double> next(const HybridBlackScholesProcess& process, vector<double> previousValue, double previousTime, double timeStep, vector<double> randomNormal) const override;
};

