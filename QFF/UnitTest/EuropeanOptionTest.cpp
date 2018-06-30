#include "gtest/gtest.h"
#include <EuropeanOption.h>
#include <BlackScholesPricer.h>
#include <BasicTradeInfo.h>
#include <MarketData.h>
#include <Aud.h>

TEST(EuropeanOptionTest, EvaluateTest) {
	EuropeanOption instrument{ BasicTradeInfo{}, "call", BlackScholesPricer{} };
	EXPECT_EQ(instrument.evaluate(MarketData{}, Aud{}), 0);
}