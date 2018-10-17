#pragma once
#include "IStochastic1FProcess.h"
#include "IParameter.h"
#include "ConstantParameter.h"
#include <memory>

using std::unique_ptr;

class GaussianShortRate1FProcess :
	public IStochastic1FProcess
{
public:
	class IDiscretisation;
	class EulerScheme;

	GaussianShortRate1FProcess() = default;
	GaussianShortRate1FProcess(unique_ptr<ConstantParameter> kappa, unique_ptr<IParameter> sigma, unique_ptr<IDiscretisation> discretisation);
	~GaussianShortRate1FProcess() = default;

	double evolve(double previousValue, double previousTime, double timeStep, double randomNormal) const override;

private:
	unique_ptr<ConstantParameter> m_kappa;
	unique_ptr<IParameter> m_sigma;
	unique_ptr<IDiscretisation> m_discretisation;
	double drift(double time, double x) const;
	double diffusion(double time) const;
	double y(double time) const;
};

class GaussianShortRate1FProcess::IDiscretisation
{
public:
	IDiscretisation() = default;
	virtual ~IDiscretisation() = default;

	virtual double next(const GaussianShortRate1FProcess& process, double previousValue, double previousTime, double timeStep, double randomNormal) const = 0;
};

class GaussianShortRate1FProcess::EulerScheme : public GaussianShortRate1FProcess::IDiscretisation
{
public:
	EulerScheme() = default;
	virtual ~EulerScheme() = default;

	double next(const GaussianShortRate1FProcess& process, double previousValue, double previousTime, double timeStep, double randomNormal) const override;
};
