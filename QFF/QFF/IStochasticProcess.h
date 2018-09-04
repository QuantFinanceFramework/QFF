#pragma once

class IStochasticProcess
{
public:
	IStochasticProcess() = default;
	virtual ~IStochasticProcess() = default;

	virtual double evolve(double previousValue, double previousTime, double timeStep, double randomNormal) const = 0;
};
