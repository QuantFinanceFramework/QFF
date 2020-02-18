#include <ModifiedFollowing.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_modified_following(py::module &m) {
  py::class_<qff::ModifiedFollowing, qff::IBusinessDayConvention>(
      m, "ModifiedFollowing")
      .def(py::init<>())
      .def("Adjust", &qff::ModifiedFollowing::Adjust, "original_date"_a,
           "calendar"_a);
}