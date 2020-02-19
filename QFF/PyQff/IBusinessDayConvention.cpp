#include <IBusinessDayConvention.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_i_business_day_convention(py::module &m) {
  py::class_<qff::IBusinessDayConvention>(m, "IBusinessDayConvention")
      .def("Adjust", &qff::IBusinessDayConvention::Adjust, "original_date"_a,
           "calendar"_a);
}