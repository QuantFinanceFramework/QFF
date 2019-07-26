#pragma once
#include <memory>
#include <string>
#include "PseudoNormalRsg.h"
#include "SobolNormalRsg.h"

namespace qff {
using std::make_unique;
using std::string;
using std::unique_ptr;

class NormalRsgFactory {
 public:
  NormalRsgFactory() = default;
  ~NormalRsgFactory() = default;
  static unique_ptr<INormalRandomSequenceGenerator> MakeNormalRsg(
      const string& rsg_name, int dimension);
};
}  // namespace qff