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

int main(void)
{
	int numbers[] = { 1, 2, 3, 4, 5 };
	const std::size_t numLen = sizeof(numbers) / sizeof(numbers[0]);

	std::cout << "Original ints: ";
	::iter(numbers, numLen, printElement<int>);
	std::cout << std::endl;

	::iter(numbers, numLen, doubleInt);
	std::cout << "Doubled ints:  ";
	::iter(numbers, numLen, printElement<int>);
	std::cout << std::endl;

	const std::string words[] = { "Alpha", "Beta", "Gamma", "Delta" };
	const std::size_t wordLen = sizeof(words) / sizeof(words[0]);

	std::cout << "Const strings: ";
	::iter(words, wordLen, printElement<std::string>);
	std::cout << std::endl;

	return 0;
}
