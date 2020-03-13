#include <ICalendar.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_i_calendar(py::module &m) {
  py::class_<qff_a::ICalendar>(m, "ICalendar")
      .def("IsHoliday", &qff_a::ICalendar::IsHoliday, "query_date"_a)
      .def("IsBusinessDay", &qff_a::ICalendar::IsBusinessDay, "query_date"_a)
      .def("IsWeekend", &qff_a::ICalendar::IsWeekend, "query_date"_a);
}