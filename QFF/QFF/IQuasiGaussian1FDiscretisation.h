#pragma once
#include "IParameter.h"
#include <vector>

using std::vector;

class IQuasiGaussian1FDiscretisation
{
public:
	IQuasiGaussian1FDiscretisation() = default;
	virtual ~IQuasiGaussian1FDiscretisation() = default;

	virtual vector <double> evolve(const IParameter& kappa, const IParameter& sigma, const IParameter& beta, const IParameter& s0, const vector <double>& previousValue, double previousTime, double timeStep, double randomNormal) const = 0;
};

