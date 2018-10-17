#include "EconomicScenarioGenerator.h"

EconomicScenarioGenerator::EconomicScenarioGenerator(double initialValue, shared_ptr<IStochastic1FProcess> process, shared_ptr<INormalRandomSequenceGenerator> normalRsg) : m_initialValue{ initialValue }, m_process{ process }, m_normalRsg{ normalRsg } {}

vector<double> EconomicScenarioGenerator::generateScenario(const vector<double>& timeGrid) const
{
	auto randomNormalSeq = m_normalRsg->generateNormalSequence();
	vector<double> result{m_initialValue};

	for (size_t i = 1; i < timeGrid.size(); i++)
	{
		double dt = timeGrid[i] - timeGrid[i-1];
		result.emplace_back(m_process->evolve(result[i - 1], timeGrid[i - 1], dt, randomNormalSeq[i-1]));
	}
	return result;
}

vector<vector<double>> EconomicScenarioGenerator::generateScenarioSet(size_t numberOfPath, const vector<double>& timeGrid) const
{
	vector<vector<double>> result;
	for (size_t i = 0; i < numberOfPath; i++)
	{
		result.emplace_back(generateScenario(timeGrid));
	}
	return result;
}
