#pragma once
#include "IStochasticProcess.h"

class IStochastic1FProcess :
	public IStochasticProcess
{
public:
	IStochastic1FProcess() = default;
	
	virtual ~IStochastic1FProcess() = default;

	vector<double> evolve(const vector<double> & previousValue, double previousTime, double timeStep, const vector<double> & randomNormal) const final;
	
	virtual double evolve(double previousValue, double previousTime, double timeStep, double randomNormal) const = 0;
	
	size_t factors() const final;
};



