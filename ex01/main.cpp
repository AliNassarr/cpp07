#include "iter.hpp"
#include <iostream>
#include <string>

template <typename T>
void printElement(const T& element)
{
	std::cout << element << " ";
}

void doubleInt(int& n)
{
	n *= 2;
}

void incrementInt(int& n)
{
	++n;
}

class Awesome
{
public:
	Awesome(void) : _n(42) {}
	Awesome(int n) : _n(n) {}
	int get(void) const { return this->_n; }
private:
	int _n;
};

std::ostream & operator<<(std::ostream & o, const Awesome &a)
{
	o << a.get();
	return o;
}

int main(void)
{
	std::cout << "=== Test 1: Non-Const Integer Array (Modification & Display) ===" << std::endl;
	int numbers[] = { 1, 2, 3, 4, 5 };
	const std::size_t numSize = sizeof(numbers) / sizeof(numbers[0]);

	std::cout << "Original:           ";
	::iter(numbers, numSize, printElement<int>);
	std::cout << std::endl;

	std::cout << "After doubleInt:    ";
	::iter(numbers, numSize, doubleInt);
	::iter(numbers, numSize, printElement<int>);
	std::cout << std::endl;

	std::cout << "After incrementInt: ";
	::iter(numbers, numSize, incrementInt);
	::iter(numbers, numSize, printElement<int>);
	std::cout << std::endl;

	std::cout << "\n=== Test 2: Const String Array ===" << std::endl;
	const std::string words[] = { "Alpha", "Beta", "Gamma", "Delta" };
	const std::size_t wordSize = sizeof(words) / sizeof(words[0]);

	std::cout << "Const words: ";
	::iter(words, wordSize, printElement<std::string>);
	std::cout << std::endl;

	std::cout << "\n=== Test 3: 42 Evaluation Sheet Test (Awesome Class) ===" << std::endl;
	Awesome awesomeArray[4];
	const std::size_t awesomeSize = sizeof(awesomeArray) / sizeof(awesomeArray[0]);

	std::cout << "Awesome array: ";
	::iter(awesomeArray, awesomeSize, printElement<Awesome>);
	std::cout << std::endl;

	std::cout << "\n=== Test 4: Null Pointer Safety ===" << std::endl;
	int* nullArr = NULL;
	::iter(nullArr, 5, printElement<int>);
	std::cout << "Successfully survived calling iter on NULL pointer!" << std::endl;

	return 0;
}
