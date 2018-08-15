#include "gtest/gtest.h"
#include <EuropeanOption.h>
#include <BlackScholesPricer.h>
#include <BasicTradeInfo.h>
#include <MarketData.h>
#include <Aud.h>
#include "MarketDataStub.h"

TEST(EuropeanOptionTest, EvaluateTest) {
	MarketDataStub data{};
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10), 1 };
	EuropeanOption instrument{ info, "call", std::make_shared<BlackScholesPricer>()};
	EXPECT_NEAR(instrument.evaluate(data, Aud{}), 7.4879, 0.0001);
}