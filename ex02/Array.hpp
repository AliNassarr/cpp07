#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>
#include <cstddef>

template <typename T>
class Array
{
public:
	Array()
		: _elements(NULL), _length(0)
	{
	}

	explicit Array(unsigned int n)
		: _elements(n > 0 ? new T[n]() : NULL), _length(n)
	{
	}

	Array(const Array& other)
		: _elements(other._length > 0 ? new T[other._length]() : NULL), _length(other._length)
	{
		for (unsigned int i = 0; i < _length; ++i)
			_elements[i] = other._elements[i];
	}

	Array& operator=(const Array& rhs)
	{
		if (this != &rhs)
		{
			T* newElements = rhs._length > 0 ? new T[rhs._length]() : NULL;
			for (unsigned int i = 0; i < rhs._length; ++i)
				newElements[i] = rhs._elements[i];

			delete[] _elements;
			_elements = newElements;
			_length = rhs._length;
		}
		return *this;
	}

	~Array()
	{
		delete[] _elements;
	}

	T& operator[](unsigned int index)
	{
		if (index >= _length)
			throw std::out_of_range("Array index out of range");
		return _elements[index];
	}

	const T& operator[](unsigned int index) const
	{
		if (index >= _length)
			throw std::out_of_range("Array index out of range");
		return _elements[index];
	}

	unsigned int size() const
	{
		return _length;
	}

private:
	T* _elements;
	unsigned int _length;
};

#endif
