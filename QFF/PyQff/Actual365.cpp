#include <Actual365.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_actual_365(py::module &m) {
  py::class_<qff::Actual365, qff::IDayCounter>(m, "Actual365")
      .def(py::init<>());
}