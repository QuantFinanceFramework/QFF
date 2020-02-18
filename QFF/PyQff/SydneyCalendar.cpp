#include <SydneyCalendar.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_sydney_calendar(py::module &m) {
  py::class_<qff::SydneyCalendar, qff::ICalendar>(m, "SydneyCalendar")
      .def(py::init<>())
      .def("IsHoliday", &qff::SydneyCalendar::IsHoliday, "query_date"_a)
      .def("IsBusinessDay", &qff::SydneyCalendar::IsBusinessDay, "query_date"_a)
      .def("IsWeekend", &qff::SydneyCalendar::IsWeekend, "query_date"_a);
}