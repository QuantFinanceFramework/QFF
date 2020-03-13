#include <NewYorkFedCalendar.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_new_york_fed_calendar(py::module &m) {
  py::class_<qff_a::NewYorkFedCalendar, qff_a::ICalendar>(m, "NewYorkFedCalendar")
      .def(py::init<>());
}