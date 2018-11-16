#pragma once
#include "IStochasticProcess.h"
class IStochasticShortRateProcess :
	public IStochasticProcess
{
public:
	IStochasticShortRateProcess() = default;
	
	virtual ~IStochasticShortRateProcess() = default;

	virtual double zeroCouponBondPrice(double t, double T, const vector<double> & state) const = 0;
};


