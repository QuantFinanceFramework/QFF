#pragma once
#include <vector>

using std::vector;

class IStochasticProcess
{
public:
	IStochasticProcess() = default;
	
	virtual ~IStochasticProcess() = default;

	virtual vector<double> evolve(const vector<double> & previousValue, double previousTime, double timeStep, const vector<double> & randomNormal) const = 0;
	
	virtual size_t factors() const = 0;
	
	virtual size_t dimension() const = 0;
};
