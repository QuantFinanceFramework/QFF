#pragma once
#include <memory>
#include "PseudoNormalRsg.h"
#include "SobolNormalRsg.h"
#include <string>

using std::unique_ptr;
using std::make_unique;
using std::string;

class NormalRsgFactory
{
public:
	NormalRsgFactory() = default;
	~NormalRsgFactory() = default;
	static unique_ptr<INormalRandomSequenceGenerator> makeNormalRsg(const string & rsgName, int dimension);
};
