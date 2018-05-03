#pragma once
class IEuropeanOptionPricer
{
public:
	IEuropeanOptionPricer() = default;
	virtual ~IEuropeanOptionPricer() = default;
	virtual double evaluate() const = 0;
};
