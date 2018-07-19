#include <memory>
#include <vector>
#include <iostream>
#include <numeric>

using namespace std;

class CashFlow {
public:
	CashFlow(double value);
	double evaluate();

private:
	double m_value;
};

CashFlow::CashFlow(double value) : m_value{ value } {};
double CashFlow::evaluate() { return m_value; };

class Collection {
public:
	Collection(vector<unique_ptr<CashFlow>> col);
	Collection(const Collection&) = delete;
	Collection(Collection&&) = default;
	double evaluate();

private:
	vector<unique_ptr<CashFlow>> m_col;
};

Collection::Collection(vector<unique_ptr<CashFlow>> col) :m_col{ move(col) } {};

double Collection::evaluate() {
	return accumulate(m_col.begin(), m_col.end(), 0.0, [&](double result, auto& p) {return result + p->evaluate(); });
};

class Swap {
public:
	Swap(Collection col1, Collection col2);
	Swap(const Swap&) = delete;
	Swap(Swap&&) = default;
	double evaluate();

private:
	Collection m_col1;
	Collection m_col2;
};

Swap::Swap(Collection col1, Collection col2) :m_col1{ move(col1) }, m_col2{ move(col2) } {};
double Swap::evaluate() {
	return m_col1.evaluate() - m_col2.evaluate();
};

int main() {

	CashFlow cf1{ 100.0 };
	cout << cf1.evaluate() << '\n';

	auto pt1 = make_unique<CashFlow>(200.0);
	cout << pt1->evaluate() << '\n';

	auto pt3(move(pt1));
	cout << pt3->evaluate() << '\n';

	vector<unique_ptr<CashFlow>> col1;
	col1.emplace_back(make_unique<CashFlow>(10.0));
	col1.push_back(make_unique<CashFlow>(11.0));

	Collection collection1(move(col1));
	cout << collection1.evaluate() << '\n';

	vector<unique_ptr<CashFlow>> col2;
	col2.emplace_back(make_unique<CashFlow>(100.0));
	col2.push_back(make_unique<CashFlow>(110.0));
	//The above 2 lines do the same things but emplace_back is more efficent.

	Collection collection2(move(col2));
	cout << collection2.evaluate() << '\n';

	Swap swap(move(collection1), move(collection2));
	cout << swap.evaluate() << '\n';

	/*
	The code below would not work.
	Collection cannot be copied.
	Collection has a vector of unique_ptr, and unique_prt cannot be copied but moved only.
	*/

	//Swap swap(collection1, collection2);
	//cout << swap.evaluate() << '\n';

	system("Pause");
	return EXIT_SUCCESS;
}