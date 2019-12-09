#include <aad_all.h>
#include <iostream>
#include <vector>

int main() {
  using namespace aad;
  auto tape = *a_double::tape;
  tape.clear();

  a_double x(15.0);
  a_double y(20.0);
  a_double z(1.0);

  auto result = a_double(x * y + z);

  result.propagate_to_start();

  std::cout << "result :" << result.value() << "\n";
  std::cout << "dresult / dx :" << x.adjoint() << "\n";
  std::cout << "dresult / dy :" << y.adjoint() << "\n";
  std::cout << "dresult / dz :" << z.adjoint() << "\n";

  tape.rewind();

  a_double a(1.0);
  a_double b(20.0);
  a_double c(30.0);

  auto result2 = a_double(exp(a) + b - pow(c, 2));

  result2.propagate_to_start();

  std::cout << "result2 :" << result2.value() << "\n";
  std::cout << "dresult2 / da :" << a.adjoint() << "\n";
  std::cout << "dresult2 / db :" << b.adjoint() << "\n";
  std::cout << "dresult2 / dc :" << c.adjoint() << "\n";

  tape.rewind();

  std::vector vx_double{1.0, 20.0, 30.0};
  std::vector<a_double> vx(3);
  convert_collection(vx_double.begin(), vx_double.end(), vx.begin());
  const auto func = [](const std::vector<a_double>& v) {
    return a_double(exp(v[0]) + v[1] - pow(v[2], 2));
  };

  auto result3 = func(vx);

  result3.propagate_to_start();

  std::cout << "result3 :" << result3.value() << "\n";
  std::cout << "dresult3 / dvx[0] :" << vx[0].adjoint() << "\n";
  std::cout << "dresult3 / dvx[1] :" << vx[1].adjoint() << "\n";
  std::cout << "dresult3 / dvx[2] :" << vx[2].adjoint() << "\n";
}
