#include "gtest/gtest.h"
#include <MarketData.h>
#include <vector>
#include <CashFlowCollection.h>
#include "CurrencyStub.h"
#include "CashFlowStub.h"
#include "MarketDataStub.h"
#include <memory>

using namespace testing;
using std::vector;
using std::unique_ptr;
using std::move;

TEST(CashFlowCollectionTest, EvaluateTest) {
	MarketDataStub data{};
	CurrencyStub currency{};
	auto pDummyCashFlow1 = std::make_unique<CashFlowStub>();
	auto pDummyCashFlow2 = std::make_unique<CashFlowStub>();
	auto pDummyCashFlow3 = std::make_unique<CashFlowStub>();

	ON_CALL(*pDummyCashFlow1, evaluate(_, _)).WillByDefault(Return(1.0));
	ON_CALL(*pDummyCashFlow2, evaluate(_, _)).WillByDefault(Return(2.0));
	ON_CALL(*pDummyCashFlow3, evaluate(_, _)).WillByDefault(Return(2.5));

	vector<unique_ptr<ICashFlow>> cashFlowVector;
	cashFlowVector.emplace_back(move(pDummyCashFlow1));
	cashFlowVector.emplace_back(move(pDummyCashFlow2));
	cashFlowVector.emplace_back(move(pDummyCashFlow3));

	CashFlowCollection bond{move(cashFlowVector)};

	EXPECT_EQ(bond.evaluate(data, currency), 5.5);
}
