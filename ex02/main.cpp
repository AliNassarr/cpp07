#include "Array.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#define MAX_VAL 750

int main(void)
{
	std::cout << "==========================================" << std::endl;
	std::cout << "  42 Official Subject Benchmark (MAX_VAL) " << std::endl;
	std::cout << "==========================================" << std::endl;
	{
		Array<int> numbers(MAX_VAL);
		int* mirror = new int[MAX_VAL];
		srand(static_cast<unsigned int>(time(NULL)));
		for (int i = 0; i < MAX_VAL; i++)
		{
			const int value = rand();
			numbers[i] = value;
			mirror[i] = value;
		}

		// Scope test: copy constructor and assignment in nested scope
		{
			Array<int> tmp = numbers;
			Array<int> test(tmp);
		}

		bool mirrorMatches = true;
		for (int i = 0; i < MAX_VAL; i++)
		{
			if (mirror[i] != numbers[i])
			{
				std::cerr << "FAIL: didn't save the same value!!" << std::endl;
				mirrorMatches = false;
				delete[] mirror;
				return 1;
			}
		}
		if (mirrorMatches)
			std::cout << "SUCCESS: All " << MAX_VAL << " elements match mirror array!" << std::endl;

		// Out-of-bounds tests from 42 subject
		try
		{
			std::cout << "Testing negative index (numbers[-2])... ";
			numbers[-2] = 0;
			std::cout << "FAILED: No exception thrown!" << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught expected exception: " << e.what() << std::endl;
		}

		try
		{
			std::cout << "Testing upper bound index (numbers[MAX_VAL])... ";
			numbers[MAX_VAL] = 0;
			std::cout << "FAILED: No exception thrown!" << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught expected exception: " << e.what() << std::endl;
		}

		delete[] mirror;
	}

	std::cout << "\n==========================================" << std::endl;
	std::cout << "  Empty Array Tests                       " << std::endl;
	std::cout << "==========================================" << std::endl;
	{
		Array<int> empty;
		std::cout << "Empty array size: " << empty.size() << std::endl;
		try
		{
			std::cout << "Attempting to access empty[0]... ";
			empty[0] = 42;
			std::cout << "FAILED: No exception thrown!" << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught expected exception: " << e.what() << std::endl;
		}
	}

	std::cout << "\n==========================================" << std::endl;
	std::cout << "  Default Value-Initialization Test       " << std::endl;
	std::cout << "==========================================" << std::endl;
	{
		Array<int> defaultInts(5);
		std::cout << "Default initialized ints (must be 0): ";
		for (unsigned int i = 0; i < defaultInts.size(); ++i)
			std::cout << defaultInts[i] << " ";
		std::cout << std::endl;
	}

	std::cout << "\n==========================================" << std::endl;
	std::cout << "  Deep Copy & Assignment Independence     " << std::endl;
	std::cout << "==========================================" << std::endl;
	{
		Array<std::string> original(3);
		original[0] = "Apple";
		original[1] = "Banana";
		original[2] = "Cherry";

		Array<std::string> copy(original);
		copy[0] = "Avocado";

		std::cout << "original[0] after modifying copy: " << original[0] << " (must be Apple)" << std::endl;
		std::cout << "copy[0]:                          " << copy[0] << " (must be Avocado)" << std::endl;

		Array<std::string> assigned;
		assigned = original;
		assigned[1] = "Blueberry";

		std::cout << "original[1] after modifying assigned: " << original[1] << " (must be Banana)" << std::endl;
		std::cout << "assigned[1]:                          " << assigned[1] << " (must be Blueberry)" << std::endl;
	}

	std::cout << "\n==========================================" << std::endl;
	std::cout << "  Const Array Correctness                 " << std::endl;
	std::cout << "==========================================" << std::endl;
	{
		Array<int> mut(3);
		mut[0] = 100;
		mut[1] = 200;
		mut[2] = 300;

		const Array<int> constArr = mut;
		std::cout << "constArr size: " << constArr.size() << std::endl;
		std::cout << "constArr elements: ";
		for (unsigned int i = 0; i < constArr.size(); ++i)
			std::cout << constArr[i] << " ";
		std::cout << std::endl;
	}

	std::cout << "\nAll Array tests completed successfully!" << std::endl;
	return 0;
}
