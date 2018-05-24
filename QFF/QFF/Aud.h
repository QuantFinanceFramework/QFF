#pragma once
#include "ICurrency.h"
class Aud :
	public ICurrency
{
public:
	Aud() = default;
	~Aud() = default;

	string getCurrency() const override;
};

