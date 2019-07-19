#pragma once
#include <IMarketData.h>
#include "gmock\gmock.h"

using namespace qff;

class MarketDataStub : public IMarketData {
 public:
  MOCK_CONST_METHOD2(getDiscountFactor, double(string curveName, date date));
  MOCK_CONST_METHOD2(getForwardRateProjection,
                     double(string curveName, date date));
  MOCK_CONST_METHOD1(getSpot, double(string underlying));
  MOCK_CONST_METHOD2(getForward, double(string curveName, date date));
  MOCK_CONST_METHOD3(getVolatility,
                     double(string underlying, date date, double strike));
};