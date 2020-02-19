#include <Thirty360Isda.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_thirty_360_isda(py::module &m) {
  py::class_<qff::Thirty360Isda, qff::IDayCounter>(m, "Thirty360Isda")
      .def(py::init<>());
}