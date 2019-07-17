#pragma once
#include <string>

namespace qff {
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
}