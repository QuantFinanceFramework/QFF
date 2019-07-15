#pragma once
#include "IProduct.h"
#include "ICashflow.h"
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class Leg :
	public IProduct
{
public:
	Leg() = default;
	Leg(vector<unique_ptr<ICashflow>> cashflows);

	Leg(const Leg&) = delete;
	Leg& operator=(const Leg&) = delete;

	Leg(Leg&&) = default;
	Leg& operator=(Leg&&) = default;

	~Leg() = default;

	Currency evaluate(const IMarketData& marketData, const string& currencyCode) const override;
	
private:
	vector<unique_ptr<ICashflow>> cashflows_;
};

