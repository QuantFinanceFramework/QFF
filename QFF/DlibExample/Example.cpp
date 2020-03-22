#include <BlackScholesFormula.h>

#include <iostream>

using namespace std;

int main() {
  try {
    const auto vol = qff_a::BlackScholesImpliedVolatility(3.0, 100.0, 100.0,
                                                          1.0, 1.0, "call");

    std::cout << vol;
  } catch (std::exception& e) {
    cout << e.what() << endl;
  }
  return 0;
}
