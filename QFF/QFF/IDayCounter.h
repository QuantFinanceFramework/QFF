#pragma once
class IDayCounter
{
public:
	IDayCounter() = default;
	virtual ~IDayCounter() = default;
	virtual double calculate() const = 0;
};


