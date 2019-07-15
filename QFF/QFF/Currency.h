#pragma once
#include <string>

using std::string;

struct Currency
{
public:
	Currency() = default;
	Currency(string currencyCode, double amount);
	~Currency() = default;

	string currencyCode;
	double amount;
};

