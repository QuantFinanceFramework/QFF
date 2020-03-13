#include <InterestRateCurve.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_interest_rate_curve(py::module &m) {
  py::class_<qff_a::InterestRateCurve<double>,
             qff_a::IInterestRateCurve<double>>(m, "InterestRateCurve")
      .def("GetCurveDate", &qff_a::InterestRateCurve<double>::GetCurveDate);
  ;
}