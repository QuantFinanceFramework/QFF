#pragma once
#include <IMarketData.h>
#include "gmock/gmock.h"

using namespace qff;
using boost::gregorian::date;
using std::string;

class MarketDataStub : public IMarketData {
 public:
  MOCK_CONST_METHOD2(GetDiscountFactor, double(string curve_name, date date));
  MOCK_CONST_METHOD3(GetVolatility,
                     double(string underlying, date date, double strike));
};