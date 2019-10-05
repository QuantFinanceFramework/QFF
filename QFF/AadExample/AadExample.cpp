#include <aad_all.h>
#include <iostream>
#include <vector>

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

  auto result2 = aad_double(exp(a) + b - pow(c, 2));

  result2.propagate_to_start();

  std::cout << "result2 :" << result2.value() << "\n";
  std::cout << "dresult2 / da :" << a.adjoint() << "\n";
  std::cout << "dresult2 / db :" << b.adjoint() << "\n";
  std::cout << "dresult2 / dc :" << c.adjoint() << "\n";

  tape.rewind();

  std::vector vx_double{1.0, 20.0, 30.0};
  std::vector<aad_double> vx(3);
  convert_collection(vx_double.begin(), vx_double.end(), vx.begin());
  const auto func = [](const std::vector<aad_double>& v) {
    return aad_double(exp(v[0]) + v[1] - pow(v[2], 2));
  };

  auto result3 = func(vx);

  result3.propagate_to_start();

  std::cout << "result3 :" << result3.value() << "\n";
  std::cout << "dresult3 / dvx[0] :" << vx[0].adjoint() << "\n";
  std::cout << "dresult3 / dvx[1] :" << vx[1].adjoint() << "\n";
  std::cout << "dresult3 / dvx[2] :" << vx[2].adjoint() << "\n";
}
