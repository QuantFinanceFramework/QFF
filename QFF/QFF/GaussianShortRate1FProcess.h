#pragma once
#include "IStochasticShortRateProcess.h"
#include "IParameter.h"
#include "ConstantParameter.h"
#include "DiscountCurve.h"
#include <memory>

using std::unique_ptr;
using std::shared_ptr;

class GaussianShortRate1FProcess :
	public IStochasticShortRateProcess
{
public:
	class IDiscretisation;
	class EulerScheme;

	GaussianShortRate1FProcess() = default;

	GaussianShortRate1FProcess(
		shared_ptr<DiscountCurve> disCurve, 
		const vector<double> & term,
		const vector<double> & kappa,
		const vector<double> & sigma,
		unique_ptr<IDiscretisation> discretisation);

	~GaussianShortRate1FProcess() = default;

	vector<double> evolve(
		const vector<double> & previousValue, 
		double previousTime, 
		double timeStep, 
		const vector<double> & randomNormal) const override;

	size_t factors() const override;

	size_t dimension() const override;

	double zeroCouponBondPrice(double t, double T, const vector<double> & state) const override;

private:
	shared_ptr<DiscountCurve> m_disCurve;
	vector<double> m_term;
	vector<double> m_kappa;
	vector<double> m_sigma;
	unique_ptr<IDiscretisation> m_discretisation;
	double drift(double time, double x) const;
	double diffusion(double time) const;
	double y(double time) const;
	double g(double t, double T) const;
};

class GaussianShortRate1FProcess::IDiscretisation
{
public:
	IDiscretisation() = default;
	virtual ~IDiscretisation() = default;

	virtual double next(const GaussianShortRate1FProcess& process, double previousValue, double previousTime, double timeStep, double randomNormal) const = 0;
};

class GaussianShortRate1FProcess::EulerScheme : 
	public GaussianShortRate1FProcess::IDiscretisation
{
public:
	EulerScheme() = default;
	virtual ~EulerScheme() = default;

	double next(const GaussianShortRate1FProcess& process, double previousValue, double previousTime, double timeStep, double randomNormal) const override;
};
