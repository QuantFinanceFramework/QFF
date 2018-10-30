#pragma once
#include "IEconomicScenarioGenerator.h"
#include "IStochastic1FProcess.h"
#include "NormalRsgFactory.h"
#include <string>
#include <memory>

using std::string;
using std::shared_ptr;

class EconomicScenarioGenerator :
	public IEconomicScenarioGenerator
{
public:
	EconomicScenarioGenerator() = delete;
	EconomicScenarioGenerator(double initialValue, shared_ptr<IStochastic1FProcess> process, const vector<double>& timeGrid, const string & rsgName);
	~EconomicScenarioGenerator() = default;

	vector<double> generateScenario() const override;
	vector<vector<double>> generateScenarioSet(size_t numberOfPath) const final;

private:
	double m_initialValue;
	shared_ptr<IStochastic1FProcess> m_process;
	vector<double> m_timeGrid;
	unique_ptr<INormalRandomSequenceGenerator> m_normalRsg;
};

