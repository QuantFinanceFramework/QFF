#include <NewYorkCalendar.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_new_york_calendar(py::module &m) {
  py::class_<qff::NewYorkCalendar>(m, "NewYorkCalendar")
      .def(py::init<>())
      .def("IsHoliday", &qff::NewYorkCalendar::IsHoliday, "query_date"_a);
}