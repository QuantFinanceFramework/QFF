#pragma once
#include <vector>

using std::vector;

class IEconomicScenarioGenerator
{
public:
	IEconomicScenarioGenerator() = default;
	virtual ~IEconomicScenarioGenerator() = default;

	virtual vector<double> generateScenario() const = 0;
	virtual vector<vector<double>> generateScenarioSet(size_t numberOfPath) const = 0;
};
