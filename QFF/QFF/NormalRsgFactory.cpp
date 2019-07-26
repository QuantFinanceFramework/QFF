#include "NormalRsgFactory.h"

namespace qff {
unique_ptr<INormalRandomSequenceGenerator> NormalRsgFactory::MakeNormalRsg(
    const string& rsg_name, int dimension) {
  if (rsg_name == "Pseudo") return make_unique<PseudoNormalRsg>(dimension);
  if (rsg_name == "Sobol")
    return make_unique<SobolNormalRsg>(dimension);
  return nullptr;
}
}  // namespace qff