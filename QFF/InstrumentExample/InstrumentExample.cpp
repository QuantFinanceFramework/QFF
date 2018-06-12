#include <EuropeanOption.h>
#include <BasicTradeInfo.h>
#include <MarketData.h>
#include <BlackScholesPricer.h>
#include <iostream>
#include <Aud.h>

int main()
{
	EuropeanOption instrument{ BasicTradeInfo{}, "call", BlackScholesPricer{} };
	std::cout << instrument.evaluate(MarketData{}, Aud{}) << '\n';
	return 0;
}

