#include "whatever.hpp"
#include <iostream>
#include <string>

class Awesome
{
public:
	Awesome(void) : _n(0) {}
	Awesome(int n) : _n(n) {}
	Awesome& operator=(Awesome const & a) { _n = a._n; return *this; }
	bool operator==(Awesome const & rhs) const { return (this->_n == rhs._n); }
	bool operator!=(Awesome const & rhs) const { return (this->_n != rhs._n); }
	bool operator>(Awesome const & rhs) const { return (this->_n > rhs._n); }
	bool operator<(Awesome const & rhs) const { return (this->_n < rhs._n); }
	bool operator>=(Awesome const & rhs) const { return (this->_n >= rhs._n); }
	bool operator<=(Awesome const & rhs) const { return (this->_n <= rhs._n); }
	int get_n() const { return _n; }
private:
	int _n;
};

std::ostream & operator<<(std::ostream & o, const Awesome &a)
{
	o << a.get_n();
	return o;
}

int main(void)
{
	std::cout << "--- 42 Subject Mandatory Tests ---" << std::endl;
	int a = 2;
	int b = 3;
	::swap(a, b);
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
	std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;

	std::string c = "chaine1";
	std::string d = "chaine2";
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
	std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;

	std::cout << "\n--- Peer Evaluation: Custom Class (Awesome) ---" << std::endl;
	Awesome aw1(21), aw2(42);
	::swap(aw1, aw2);
	std::cout << "aw1 = " << aw1 << ", aw2 = " << aw2 << std::endl;
	std::cout << "min( aw1, aw2 ) = " << ::min(aw1, aw2) << std::endl;
	std::cout << "max( aw1, aw2 ) = " << ::max(aw1, aw2) << std::endl;

	std::cout << "\n--- Peer Evaluation: Return 2nd Parameter on Equality ---" << std::endl;
	int eq1 = 42;
	int eq2 = 42;
	std::cout << "Address of eq1: " << &eq1 << std::endl;
	std::cout << "Address of eq2: " << &eq2 << std::endl;
	std::cout << "Address returned by min(eq1, eq2): " << &::min(eq1, eq2) << " (matches eq2: " << (&::min(eq1, eq2) == &eq2 ? "YES" : "NO") << ")" << std::endl;
	std::cout << "Address returned by max(eq1, eq2): " << &::max(eq1, eq2) << " (matches eq2: " << (&::max(eq1, eq2) == &eq2 ? "YES" : "NO") << ")" << std::endl;

	return 0;
}