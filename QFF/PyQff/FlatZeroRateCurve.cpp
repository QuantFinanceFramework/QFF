#include <FlatZeroRateCurve.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_flat_zero_rate_curve(py::module &m) {
  py::class_<qff_a::FlatZeroRateCurve<double>, qff_a::InterestRateCurve<double>,
             qff_a::IInterestRateCurve<double>>(m, "FlatZeroRateCurve")
      .def(py::init<boost::gregorian::date, std::string,
                    const qff_a::IDayCounter &, double>());
}