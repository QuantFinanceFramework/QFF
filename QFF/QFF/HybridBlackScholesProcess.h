#pragma once
#include "IStochasticProcess.h"
#include "IStochasticShortRateProcess.h"
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

	HybridBlackScholesProcess(
		unique_ptr<IStochasticShortRateProcess> domesticSRProcess, 
		unique_ptr<IStochasticShortRateProcess> foreignSRProcess, 
		unique_ptr<IParameter> sigma, 
		unique_ptr<IDiscretisation> discretisation, 
		const vector<vector<double>>& correlationMatrix);

	~HybridBlackScholesProcess() = default;

	vector<double> evolve(
		const vector<double> & previousValue, 
		double previousTime, 
		double timeStep, 
		const vector<double> & randomNormal) const override;

	size_t factors() const override;

	size_t dimension() const override;

private:
	unique_ptr<IStochasticShortRateProcess> m_domesticSRProcess;
	unique_ptr<IStochasticShortRateProcess> m_foreignSRProcess;
	unique_ptr<IParameter> m_sigma;
	unique_ptr<IDiscretisation> m_discretisation;
	vector<vector<double>> m_correlationMatrix;
	double diffusion(double time, double s) const;
};

class HybridBlackScholesProcess::IDiscretisation
{
public:
	IDiscretisation() = default;
	virtual ~IDiscretisation() = default;

	virtual vector<double> next(
		const HybridBlackScholesProcess& process, 
		const vector<double> & previousValue, 
		double previousTime, 
		double timeStep, 
		const vector<double> & randomNormal) const = 0;
};

class HybridBlackScholesProcess::ExactScheme : 
	public HybridBlackScholesProcess::IDiscretisation
{
public:
	ExactScheme() = default;
	virtual ~ExactScheme() = default;

	vector<double> next(
		const HybridBlackScholesProcess& process, 
		const vector<double> & previousValue, 
		double previousTime, 
		double timeStep, 
		const vector<double> & randomNormal) const override;
};


