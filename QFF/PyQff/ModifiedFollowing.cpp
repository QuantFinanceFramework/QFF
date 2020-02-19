#include <ModifiedFollowing.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_modified_following(py::module &m) {
  py::class_<qff::ModifiedFollowing, qff::IBusinessDayConvention>(
      m, "ModifiedFollowing")
      .def(py::init<>());
}