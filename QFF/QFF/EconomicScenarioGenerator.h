#pragma once
#include "IEconomicScenarioGenerator.h"
#include "IStochasticProcess.h"
#include "INormalRandomSequenceGenerator.h"
#include <memory>

using std::shared_ptr;
using std::make_shared;

class EconomicScenarioGenerator :
	public IEconomicScenarioGenerator
{
public:
	EconomicScenarioGenerator() = delete;
	EconomicScenarioGenerator(double initialValue, shared_ptr<IStochasticProcess> process, shared_ptr<INormalRandomSequenceGenerator> normalRsg);
	~EconomicScenarioGenerator() = default;

	vector<double> generateScenario(vector<double> timeGrid) const override;
	vector < vector<double>> generateScenarioSet(int numberOfPath, vector<double> timeGrid) const final;

private:
	double m_initialValue;
	shared_ptr<IStochasticProcess> m_process;
	shared_ptr<INormalRandomSequenceGenerator> m_normalRsg;
	
};

