#include <BlackScholesFormula.h>
#include <pybind11/pybind11.h>

PYBIND11_MODULE(pyqff, m) {
  m.def("black_scholes_formula", &qff::BlackScholesFormula, "Black Scholes Formula from C++");
}
