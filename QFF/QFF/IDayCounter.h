#pragma once
class IDayCounter
{
public:
	IDayCounter() = default;
	virtual ~IDayCounter() = default;
	virtual double countDayBetween() const = 0;
	virtual double calculateYearFraction() const = 0;
};

