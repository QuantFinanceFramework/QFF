#pragma once
#include "IGaussian1FDiscretisation.h"

class Gaussian1FEulerScheme :
	public IGaussian1FDiscretisation
{
public:
	Gaussian1FEulerScheme() = default;
	~Gaussian1FEulerScheme()= default;

	double evolve(const IParameter& kappa, const IParameter& sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const override;

private:
	double drift(const IParameter& kappa, const IParameter& sigma, double previousValue, double previousTime, double timeStep) const;
	double diffusion(const IParameter& sigma, double previousValue, double previousTime, double timeStep, double randomNormal) const;
	double y(const IParameter& kappa, const IParameter& sigma, double previousTime) const;


};

