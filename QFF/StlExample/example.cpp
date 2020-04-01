#include <boost/range/combine.hpp>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  map<string, double> m;
  m.emplace(make_pair("abc", 2.5));
  m.emplace(make_pair("def", 3.0));
  m.emplace(make_pair("ijk", 3.5));
  m.emplace(make_pair("xyz", 4.0));
  m.emplace(make_pair("zzz", 1.5));

  vector<double> v{9.0, 8.0, 7.0, 6.0, 5.0};

  for (const auto& [key, value] : m) {
    cout << key << " has value " << value << endl;
  }
  cout << endl;

  for (auto& [key, value] : m) {
    value = value + 1.0;
  }
  cout << endl;

  for (const auto& [key, value] : m) {
    cout << key << " has value " << value << endl;
  }
  cout << endl;

  for (auto [map, value_new] : boost::combine(m, v)) {
    map.second = value_new.head;
  }
  cout << endl;

  for (const auto& [key, value] : m) {
    cout << key << " has value " << value << endl;
  }
  cout << endl;

  m.clear();

  return EXIT_SUCCESS;
}