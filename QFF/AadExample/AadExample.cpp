#include <iostream>
#include <aad_all.h>

int main() {
  using namespace aad;
  auto tape = *aad_double::tape;
  tape.clear();

  aad_double x(15.0);
  aad_double y(20.0);
  aad_double z(1.0);

  auto result = aad_double(x * y + z);

  result.propagate_to_start();

  std::cout << "result :" << result.value() << "\n";
  std::cout << "dresult / dx :" << x.adjoint() << "\n";
  std::cout << "dresult / dy :" << y.adjoint() << "\n";
  std::cout << "dresult / dz :" << z.adjoint() << "\n";

  tape.rewind();

  aad_double a(1.0);
  aad_double b(20.0);
  aad_double c(30.0);

  auto result2 = aad_double(exp(a) + b - c * c);

  result2.propagate_to_start();

  std::cout << "result2 :" << result2.value() << "\n";
  std::cout << "dresult2 / da :" << a.adjoint() << "\n";
  std::cout << "dresult2 / db :" << b.adjoint() << "\n";
  std::cout << "dresult2 / dc :" << c.adjoint() << "\n";
}
