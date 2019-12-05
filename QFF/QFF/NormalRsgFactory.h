#pragma once
#include <memory>
#include <string_view>
#include "PseudoNormalRsg.h"
#include "SobolNormalRsg.h"

namespace qff {
class NormalRsgFactory {
 public:
  static std::unique_ptr<INormalRandomSequenceGenerator> MakeNormalRsg(
     std::string_view rsg_name, int dimension);
};
}  // namespace qff