#include "IStochastic1FProcess.h"

vector<double> IStochastic1FProcess::evolve(vector<double> previousValue, double previousTime, double timeStep, vector<double> randomNormal) const
{
	return vector<double>(evolve(previousValue[0], previousTime, timeStep, randomNormal[0]));
}
