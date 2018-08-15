//#include "gtest/gtest.h"
//#include <MarketData.h>
//#include <vector>
//#include <CashFlowCollection.h>
//#include "CurrencyStub.h"
//#include "CashFlowStub.h"
//#include "MarketDataStub.h"
//#include <memory>
//
//using namespace testing;
//using std::vector;
//using std::unique_ptr;
//using std::move;
//
//TEST(SwapLegTest, EvaluateTest) {
//	MarketDataStub data{};
//	CurrencyStub currency{};
//	CashFlowStub* pDummyCashFlow1 = new CashFlowStub{};
//	CashFlowStub* pDummyCashFlow2 = new CashFlowStub{};
//	CashFlowStub* pDummyCashFlow3 = new CashFlowStub{};
//
//	ON_CALL(*pDummyCashFlow1, evaluate(_, _)).WillByDefault(Return(1.0));
//	ON_CALL(*pDummyCashFlow2, evaluate(_, _)).WillByDefault(Return(2.0));
//	ON_CALL(*pDummyCashFlow3, evaluate(_, _)).WillByDefault(Return(2.5));
//	
//	unique_ptr<CashFlowStub> p1 {pDummyCashFlow1};
//	unique_ptr<CashFlowStub> p2	{pDummyCashFlow2};
//	unique_ptr<CashFlowStub> p3	{pDummyCashFlow3};
//	
//	CashFlowCollection bond{ vector<unique_ptr<ICashFlow>>{move(p1), move(p2), move(p3)} };
//
//	EXPECT_EQ(bond.evaluate(data, currency), 5.5);
//}
