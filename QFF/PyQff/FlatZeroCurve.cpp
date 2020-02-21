#include <FlatZeroCurve.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_flat_zero_curve(py::module &m) {
  py::class_<qff::FlatZeroCurve, qff::IInterestRateCurve>(m, "FlatZeroCurve")
      .def(py::init<boost::gregorian::date, double, const qff::IDayCounter &>())
      .def("GetCurveDate", &qff::FlatZeroCurve::GetCurveDate);
}