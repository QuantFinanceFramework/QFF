#include <random>
#include <PseudoNormalRsg.h>
#include <iostream>
#include <BlackScholesProcess.h>
#include <EulerScheme.h>
#include <ExactScheme.h>
#include <EconomicScenarioGenerator.h>
#include <numeric>

int main() 
{	
	double initialPrice{ 100.0 };
	auto process = make_shared<BlackScholesProcess>(0.05, 0.2, make_shared<ExactScheme>());
	auto rsq = make_shared<PseudoNormalRsg>(1, 10);

	EconomicScenarioGenerator esg{ initialPrice, process, rsq };

	vector<double> timeGrid(10);
	std::iota(timeGrid.begin(), timeGrid.end(), 1);

	auto es = esg.generateScenarioSet(10, timeGrid);

	for (auto &i : es)
	{
		for (auto &j :i)
		{
			std::cout << j << " ";
		}
		std::cout << "\n";
	}
	system("pause");

	return 0;
}