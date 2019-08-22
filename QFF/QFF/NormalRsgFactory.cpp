#include "NormalRsgFactory.h"

using std::make_unique;
using std::string_view;
using std::unique_ptr;

namespace qff {
unique_ptr<INormalRandomSequenceGenerator> NormalRsgFactory::MakeNormalRsg(
    string_view rsg_name, int dimension) {
  if (rsg_name == "Pseudo") return make_unique<PseudoNormalRsg>(dimension);
  if (rsg_name == "Sobol") return make_unique<SobolNormalRsg>(dimension);
  return nullptr;
}
}  // namespace qff