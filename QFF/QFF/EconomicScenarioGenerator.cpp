#include "EconomicScenarioGenerator.h"

EconomicScenarioGenerator::EconomicScenarioGenerator(
	double initialValue, 
	shared_ptr<IStochastic1FProcess> process,
	const vector<double>& timeGrid,
	const string & rsgName) : 
	m_initialValue{ initialValue }, 
	m_process{ process }, 
	m_timeGrid{ timeGrid },
	m_normalRsg{ NormalRsgFactory::makeNormalRsg(rsgName, m_timeGrid.size() + m_process->numberOfFactors()) } {}

vector<double> EconomicScenarioGenerator::generateScenario() const
{
	auto randomNormalSeq = m_normalRsg->generateNormalSequence();
	vector<double> result{m_initialValue};

	for (size_t i = 1; i < m_timeGrid.size(); i++)
	{
		double dt = m_timeGrid[i] - m_timeGrid[i-1];
		result.emplace_back(m_process->evolve(result[i - 1], m_timeGrid[i - 1], dt, randomNormalSeq[i-1]));
	}
	return result;
}

vector<vector<double>> EconomicScenarioGenerator::generateScenarioSet(size_t numberOfPath) const
{
	vector<vector<double>> result(numberOfPath, vector<double>(m_timeGrid.size()));
	for (size_t i = 0; i < numberOfPath; i++)
	{
		result[i] = (generateScenario());
	}
	return result;
}
