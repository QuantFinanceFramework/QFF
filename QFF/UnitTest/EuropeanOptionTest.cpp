#include "gtest/gtest.h"
#include <EuropeanOption.h>
#include <BlackScholesPricer.h>
#include <BasicTradeInfo.h>
#include <MarketData.h>
#include <Aud.h>

TEST(EuropeanOptionTest, EvaluateTest) {
	MarketData data{ 50, 0.25, 0.1, 0.0 };
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10), 1 };
	EuropeanOption instrument{ info, "call", BlackScholesPricer{} };
	EXPECT_NEAR(instrument.evaluate(data, Aud{}), 7.4879, 0.0001);
}