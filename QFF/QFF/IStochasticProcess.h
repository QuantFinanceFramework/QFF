#pragma once
#include <vector>

using std::vector;

class IStochasticProcess
{
public:
	IStochasticProcess() = default;
	virtual ~IStochasticProcess() = default;

	virtual vector<double> evolve(vector<double> previousValue, double previousTime, double timeStep, vector<double> randomNormal) const = 0;
};
