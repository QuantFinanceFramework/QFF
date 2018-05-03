#pragma once
class IInstrument
{
public:
	IInstrument() = default;
	virtual ~IInstrument() = default;

	virtual double evaluate() const =0 ;
};

