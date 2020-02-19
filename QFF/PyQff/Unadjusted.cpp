#include <Unadjusted.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_unadjusted(py::module &m) {
  py::class_<qff::Unadjusted, qff::IBusinessDayConvention>(m, "Unadjusted")
      .def(py::init<>());
}