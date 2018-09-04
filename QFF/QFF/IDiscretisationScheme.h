#pragma once
#include <memory>

using std::shared_ptr;
using std::make_shared;

class IDiscretisationScheme
{
public:
	IDiscretisationScheme() = default;
	virtual ~IDiscretisationScheme() = default;

	virtual double evolve(double mu, double sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const = 0;
};


