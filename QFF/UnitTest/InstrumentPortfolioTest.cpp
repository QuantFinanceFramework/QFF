#pragma once
#include "gtest\gtest.h"
#include <MarketData.h>
#include <BasicTradeInfo.h>
#include <boost\date_time\gregorian\gregorian.hpp>
#include <vector>
#include <InstrumentPortfolio.h>
#include "CurrencyStub.h"
#include "InstrumentStub.h"
#include "MarketDataStub.h"
#include <memory>

using namespace testing;
using std::vector;
using std::shared_ptr;

TEST(InstrumentPortfolioTest, EvaluateTest) {

	MarketDataStub data{};
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10) };
	CurrencyStub currency{};
	auto pDummyInstrument1 = std::make_shared<InstrumentStub>();
	auto pDummyInstrument2 = std::make_shared<InstrumentStub>();
	auto pDummyInstrument3 = std::make_shared<InstrumentStub>();
	auto pDummyInstrument4 = std::make_shared<InstrumentStub>();

	InstrumentPortfolio IP{ vector<shared_ptr<IInstrument>>{pDummyInstrument1, pDummyInstrument2, pDummyInstrument3, pDummyInstrument4} };
	ON_CALL(*pDummyInstrument1, evaluate(_, _)).WillByDefault(Return(1.0));
	ON_CALL(*pDummyInstrument2, evaluate(_, _)).WillByDefault(Return(1.0));
	ON_CALL(*pDummyInstrument3, evaluate(_, _)).WillByDefault(Return(1.5));
	ON_CALL(*pDummyInstrument4, evaluate(_, _)).WillByDefault(Return(2.0));

	EXPECT_EQ(IP.evaluate(data, currency), 5.5);

}