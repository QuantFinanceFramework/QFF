#pragma once
#include "IStochastic1FProcess.h"
#include "IParameter.h"
#include <memory>

using std::unique_ptr;

class BlackScholesProcess :
	public IStochastic1FProcess
{
	class IDiscretisation;
	class ExactScheme;
	class EulerScheme;

public:
	BlackScholesProcess() = default;
	BlackScholesProcess(unique_ptr<IParameter> mu, unique_ptr<IParameter> sigma, unique_ptr<IDiscretisation> discretisation);
	~BlackScholesProcess() = default;

	double evolve(double previousValue, double previousTime, double timeStep, double randomNormal) const override;

private:
	unique_ptr<IParameter> m_mu;
	unique_ptr<IParameter> m_sigma;
	unique_ptr<IDiscretisation> m_discretisation;
	double drift(double time) const;
	double diffusion(double time, double s) const;
};

class BlackScholesProcess::IDiscretisation
{
public:
	IDiscretisation() = default;
	virtual ~IDiscretisation() = default;

	virtual double next(const BlackScholesProcess& process, double previousValue, double previousTime, double timeStep, double randomNormal) const = 0;
};

class BlackScholesProcess::ExactScheme : public BlackScholesProcess::IDiscretisation
{
public:
	ExactScheme() = default;
	virtual ~ExactScheme() = default;

	double next(const BlackScholesProcess& process, double previousValue, double previousTime, double timeStep, double randomNormal) const override;
};

class BlackScholesProcess::EulerScheme : public BlackScholesProcess::IDiscretisation
{
public:
	EulerScheme() = default;
	virtual ~EulerScheme() = default;

	double next(const BlackScholesProcess& process, double previousValue, double previousTime, double timeStep, double randomNormal) const override;
};