#include <SurvivalCurve.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_survival_curve(py::module &m) {
  py::class_<qff_a::SurvivalCurve<double>, qff_a::ICreditCurve<double>>(
      m, "SurvivalCurve")
      .def(py::init<boost::gregorian::date, std::vector<boost::gregorian::date>,
                    const std::vector<double> &,
                    const qff_a::IInterpolator<double> &,
                    const qff_a::IDayCounter &>());
}