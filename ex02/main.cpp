#include "Array.hpp"
#include <iostream>
#include <string>

int main(void)
{
	// 1. Default constructor (empty array)
	Array<int> empty;
	std::cout << "Empty array size: " << empty.size() << std::endl;

	// 2. Parametric constructor and element assignment
	Array<int> numbers(5);
	std::cout << "Numbers size: " << numbers.size() << std::endl;
	for (unsigned int i = 0; i < numbers.size(); ++i)
		numbers[i] = (i + 1) * 10;

	std::cout << "Numbers elements: ";
	for (unsigned int i = 0; i < numbers.size(); ++i)
		std::cout << numbers[i] << " ";
	std::cout << std::endl;

	// 3. Deep copy verification (modifying copy must not affect original)
	Array<int> copy(numbers);
	copy[0] = 999;
	std::cout << "Original numbers[0] after modifying copy: " << numbers[0] << std::endl;
	std::cout << "Copy copy[0]:                             " << copy[0] << std::endl;

	// 4. Testing with string type
	Array<std::string> strings(3);
	strings[0] = "Hello";
	strings[1] = "World";
	strings[2] = "42";
	std::cout << "Strings elements: ";
	for (unsigned int i = 0; i < strings.size(); ++i)
		std::cout << strings[i] << " ";
	std::cout << std::endl;

	// 5. Out of bounds exception test
	try
	{
		std::cout << "Accessing index 10 in size 5 array: ";
		numbers[10] = 42;
	}
	catch (const std::exception& e)
	{
		std::cout << "Caught expected exception: " << e.what() << std::endl;
	}

	return 0;
}
