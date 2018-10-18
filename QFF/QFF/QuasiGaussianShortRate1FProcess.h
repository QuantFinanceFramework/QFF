#pragma once
#include "IStochasticProcess.h"
#include "IParameter.h"
#include "ConstantParameter.h"
#include "DiscountCurve.h"
#include <memory>

using std::unique_ptr;
using std::shared_ptr;

class QuasiGaussianShortRate1FProcess :
	public IStochasticProcess
{
public:
	class IDiscretisation;
	class EulerScheme;

	QuasiGaussianShortRate1FProcess() = default;
	QuasiGaussianShortRate1FProcess(shared_ptr<DiscountCurve> disCurve, unique_ptr<ConstantParameter> kappa, unique_ptr<IParameter> lamda_r, unique_ptr<IParameter> beta_r, unique_ptr<IParameter> alpha_r, unique_ptr<IDiscretisation> discretisation);

	~QuasiGaussianShortRate1FProcess() = default;

	vector<double> evolve(vector<double> previousValues, double previousTime, double timeStep, vector<double> randomNormal) const override;
	double zeroCouponBondPrice(double t, double T, vector<double> state) const;

private:
	shared_ptr<DiscountCurve> m_disCurve;
	unique_ptr<ConstantParameter> m_kappa;
	unique_ptr<IParameter> m_lamda_r;
	unique_ptr<IParameter> m_beta_r;
	unique_ptr<IParameter> m_alpha_r;
	unique_ptr<IDiscretisation> m_discretisation;
	double xDrift(double time, double x, double y) const;
	double yDrift(double time, double x, double y) const;
	double xDiffusion(double time, double x) const;
	double g(double t, double T) const;
};

class QuasiGaussianShortRate1FProcess::IDiscretisation
{
public:
	IDiscretisation() = default;
	virtual ~IDiscretisation() = default;

	virtual vector<double> next(const QuasiGaussianShortRate1FProcess& process, vector<double> previousValues, double previousTime, double timeStep, double randomNormal) const = 0;
};

class QuasiGaussianShortRate1FProcess::EulerScheme : public QuasiGaussianShortRate1FProcess::IDiscretisation
{
public:
	EulerScheme() = default;
	virtual ~EulerScheme() = default;

	vector<double> next(const QuasiGaussianShortRate1FProcess& process, vector<double> previousValues, double previousTime, double timeStep, double randomNormal) const override;
};
