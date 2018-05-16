#pragma once
#include <string>
using std::string;

class ICurrency
{
public:
	virtual string getCurrency() const = 0;
	virtual ~ICurrency() = default;
};
