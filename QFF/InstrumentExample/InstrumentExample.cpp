#include <EuropeanOption.h>
#include <MarketData.h>
#include <BlackScholesPricer.h>
#include <iostream>
#include <Aud.h>

int main()
{
	EuropeanOption instrument{ EuroOptionInfo{}, "call", std::make_shared<BlackScholesPricer>() };
	std::cout << instrument.evaluate(MarketData{}, Aud{}) << '\n';
	return 0;
}

