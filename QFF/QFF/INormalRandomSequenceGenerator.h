#pragma once
#include <vector>

using std::vector;

class INormalRandomSequenceGenerator
{
public:
	INormalRandomSequenceGenerator() = default;
	virtual ~INormalRandomSequenceGenerator() = default;
	
	virtual vector<double> generateNormalSequence() = 0;
	virtual void setDimension(size_t dimension) = 0;
};
