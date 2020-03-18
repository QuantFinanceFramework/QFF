#include <IPricingEnvironment.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_i_pricing_environment(py::module &m) {
  py::class_<qff_a::IPricingEnvironment<double>>(m, "IPricingEnvironment")
      .def("GetPricingDate",
           &qff_a::IPricingEnvironment<double>::GetPricingDate)
      .def("GetDiscountFactor",
           &qff_a::IPricingEnvironment<double>::GetDiscountFactor)
      .def("GetSurvivalProbability",
           &qff_a::IPricingEnvironment<double>::GetSurvivalProbability)
      .def("GetPastRateFixing",
           &qff_a::IPricingEnvironment<double>::GetPastRateFixing);
}