#include <Actual360.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_actual_360(py::module &m) {
  py::class_<qff::Actual360, qff::IDayCounter>(m, "Actual360")
      .def(py::init<>());
}