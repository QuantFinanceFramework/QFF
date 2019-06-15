#include "IStochastic1FProcess.h"

vector<double> IStochastic1FProcess::evolve(
	const vector<double> & previousValue, 
	double previousTime, 
	double timeStep, 
	const vector<double> & randomNormal) const
{
	return vector<double>{evolve(previousValue[0], previousTime, timeStep, randomNormal[0])};
}

size_t IStochastic1FProcess::factors() const
{
	return 1;
}
