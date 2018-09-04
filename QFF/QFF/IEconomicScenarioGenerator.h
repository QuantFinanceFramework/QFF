#pragma once
#include <vector>

using std::vector;

class IEconomicScenarioGenerator
{
public:
	IEconomicScenarioGenerator() = default;
	virtual ~IEconomicScenarioGenerator() = default;

	virtual vector<double> generateScenario(vector<double> timeGrid) const = 0;
	virtual vector < vector<double>> generateScenarioSet(int numberOfPath, vector<double> timeGrid) const = 0;
};
