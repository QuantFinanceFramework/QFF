#pragma once
#include "IEconomicScenarioGenerator.h"
#include "IStochasticProcess.h"
#include "NormalRsgFactory.h"
#include <string>
#include <memory>
#include <vector>

using std::string;
using std::shared_ptr;

class EconomicScenarioGenerator :
	public IEconomicScenarioGenerator
{
public:
	EconomicScenarioGenerator() = delete;
	EconomicScenarioGenerator(const vector<double> & initialValues, shared_ptr<IStochasticProcess> process, const vector<double>& timeGrid, const string & rsgName);
	~EconomicScenarioGenerator() = default;

	vector<vector<double>> generateScenario() const override;
	vector<vector<vector<double>>> generateScenarioSet(size_t numberOfPath) const final;

private:
	vector<double> m_initialValues;
	shared_ptr<IStochasticProcess> m_process;
	vector<double> m_timeGrid;
	unique_ptr<INormalRandomSequenceGenerator> m_normalRsg;
};

