#include <Preceding.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_preceding(py::module &m) {
  py::class_<qff_a::Preceding, qff_a::IBusinessDayConvention>(m, "Preceding")
      .def(py::init<>());
}