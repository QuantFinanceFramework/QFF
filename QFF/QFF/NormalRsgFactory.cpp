#include "NormalRsgFactory.h"

unique_ptr<INormalRandomSequenceGenerator> NormalRsgFactory::makeNormalRsg(const string & rsgName, int dimension)
{
	if (rsgName == "Pseudo")
		return make_unique<PseudoNormalRsg>(dimension);
	if (rsgName == "Sobol")
		return make_unique<SobolNormalRsg>(dimension);
	else
		return nullptr;
}
