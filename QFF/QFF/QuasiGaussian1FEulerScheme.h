#pragma once
#include "IQuasiGaussian1FDiscretisation.h"

class QuasiGaussian1FEulerScheme :
	public IQuasiGaussian1FDiscretisation
{
public:
	QuasiGaussian1FEulerScheme() = default;
	~QuasiGaussian1FEulerScheme() = default;

	vector<double> evolve(const IParameter& kappa, const IParameter& sigma, const IParameter& beta, const IParameter& s0, const vector <double>& previousValue, double previousTime, double timeStep, double randomNormal) const override;

private:
	vector<double> drift(const IParameter& kappa, const IParameter& sigma, const IParameter & beta, const IParameter & s0, const vector<double>& previousValue, double previousTime, double timeStep) const;
	vector<double> diffusion(const IParameter& sigma, const IParameter & beta, const IParameter & s0, const vector<double>& previousValue, double previousTime, double timeStep, double randomNormal) const;
	double sigmaR(const IParameter& sigma, const IParameter& beta, const IParameter& s0, const vector<double>& previousValue, double previousTime) const;

};

