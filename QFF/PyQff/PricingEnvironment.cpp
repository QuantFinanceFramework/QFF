#include <PricingEnvironment.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_pricing_environment(py::module &m) {
  py::class_<qff_a::PricingEnvironment<double>,
             qff_a::IPricingEnvironment<double>>(m, "PricingEnvironment");
}