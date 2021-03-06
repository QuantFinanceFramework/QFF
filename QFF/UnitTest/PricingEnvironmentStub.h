#pragma once
#include <IPricingEnvironment.h>
#include "gmock/gmock.h"

using namespace qff_a;
using boost::gregorian::date;
using std::string;

template<typename T>
class PricingEnvironmentStub : public IPricingEnvironment<T> {
 public:
  MOCK_CONST_METHOD2(GetDiscountFactor, double(string curve_name, date date));
  MOCK_CONST_METHOD3(GetVolatility,
                     double(string underlying, date date, double strike));
};