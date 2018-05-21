#pragma once
#include "gtest\gtest.h"
#include <MarketData.h>
#include <BasicTradeInfo.h>
#include <boost\date_time\gregorian\gregorian.hpp>
#include <vector>
#include <InstrumentPortfolio.h>
#include "CurrencyStub.h"
#include "InstrumentStub.h"

using namespace testing;
using std::vector;

TEST(InstrumentPortfolioTest, EvaluateTest) {

	MarketData data{ 0.0, 0.0, 0.0 };
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10) };
	CurrencyStub currency{};
	InstrumentStub dummyInstrument1{}; 
	InstrumentStub dummyInstrument2{};
	InstrumentStub dummyInstrument3{};
	InstrumentStub dummyInstrument4{};
	InstrumentPortfolio IP{vector<IInstrument*> {&dummyInstrument1, &dummyInstrument2, &dummyInstrument3, &dummyInstrument4}};

	ON_CALL(dummyInstrument1, evaluate(_,_)).WillByDefault(Return(1.0));
	ON_CALL(dummyInstrument2, evaluate(_, _)).WillByDefault(Return(1.0));
	ON_CALL(dummyInstrument3, evaluate(_, _)).WillByDefault(Return(1.5));
	ON_CALL(dummyInstrument4, evaluate(_, _)).WillByDefault(Return(2.0));

	EXPECT_EQ(IP.evaluate(data, currency), 5.5);

}