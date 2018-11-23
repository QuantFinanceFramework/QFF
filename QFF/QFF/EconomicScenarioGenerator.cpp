#include "EconomicScenarioGenerator.h"

EconomicScenarioGenerator::EconomicScenarioGenerator(
	const vector<double> & initialValues, 
	shared_ptr<IStochasticProcess> process,
	const vector<double>& timeGrid,
	const string & rsgName) : 
	m_initialValues{ initialValues }, 
	m_process{ process }, 
	m_timeGrid{ timeGrid },
	m_normalRsg{ NormalRsgFactory::makeNormalRsg(rsgName, (m_timeGrid.size()-1) * m_process->factors()) } {}

vector<vector<double>> EconomicScenarioGenerator::generateScenario() const
{
	auto randomNormalSeq = m_normalRsg->generateNormalSequence();
	vector<vector<double>> result(m_timeGrid.size(), vector<double>(m_process->dimension()));
	result[0] = m_initialValues;
	for (size_t i = 1; i < m_timeGrid.size(); i++)
	{
		double dt = m_timeGrid[i] - m_timeGrid[i-1];
		vector<double> randomNormals{ randomNormalSeq.begin() + m_process->factors() * (i - 1), randomNormalSeq.begin() + m_process->factors() * i};
		result[i] = m_process->evolve(result[i - 1], m_timeGrid[i - 1], dt, randomNormals);
	}
	return result;
}

vector<vector<vector<double>>> EconomicScenarioGenerator::generateScenarioSet(size_t numberOfPath) const
{
	vector<vector<vector<double>>> result(numberOfPath, vector<vector<double>>(m_timeGrid.size(), vector<double>(m_process->dimension())));
	for (size_t i = 0; i < numberOfPath; i++)
	{
		result[i] = generateScenario();
	}
	return result;
}
