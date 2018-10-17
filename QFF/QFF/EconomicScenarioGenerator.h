#pragma once
#include "IEconomicScenarioGenerator.h"
#include "IStochastic1FProcess.h"
#include "INormalRandomSequenceGenerator.h"
#include <memory>

using std::shared_ptr;

class EconomicScenarioGenerator :
	public IEconomicScenarioGenerator
{
public:
	EconomicScenarioGenerator() = delete;
	EconomicScenarioGenerator(double initialValue, shared_ptr<IStochastic1FProcess> process, shared_ptr<INormalRandomSequenceGenerator> normalRsg);
	~EconomicScenarioGenerator() = default;

	vector<double> generateScenario(const vector<double>& timeGrid) const override;
	vector<vector<double>> generateScenarioSet(size_t numberOfPath, const vector<double>& timeGrid) const final;

private:
	double m_initialValue;
	shared_ptr<IStochastic1FProcess> m_process;
	shared_ptr<INormalRandomSequenceGenerator> m_normalRsg;
	
};

