#include "EconomicScenarioGenerator.h"

EconomicScenarioGenerator::EconomicScenarioGenerator(double initialValue, shared_ptr<IStochastic1FProcess> process, shared_ptr<INormalRandomSequenceGenerator> normalRsg) : m_initialValue{ initialValue }, m_process{ process }, m_normalRsg{ normalRsg } {}

vector<double> EconomicScenarioGenerator::generateScenario(vector<double> timeGrid) const
{
	vector<double> result{m_initialValue};

	for (size_t i = 1; i < timeGrid.size(); i++)
	{
		double dt = timeGrid[i] - timeGrid[i-1];
		auto randomNormalSeq = m_normalRsg->generateNormalSequence();
		result.emplace_back(m_process->evolve(result[i - 1], timeGrid[i - 1], dt, randomNormalSeq[0]));
	}
	return result;
}

vector<vector<double>> EconomicScenarioGenerator::generateScenarioSet(int numberOfPath, vector<double> timeGrid) const
{
	vector<vector<double>> result;
	for (size_t i = 0; i < numberOfPath; i++)
	{
		result.emplace_back(generateScenario(timeGrid));
	}
	return result;
}
