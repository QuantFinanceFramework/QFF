#include <Unadjusted.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_unadjusted(py::module &m) {
  py::class_<qff::Unadjusted, qff::IBusinessDayConvention>(m, "Unadjusted")
      .def(py::init<>())
      .def("Adjust", &qff::Unadjusted::Adjust, "original_date"_a, "calendar"_a);
}