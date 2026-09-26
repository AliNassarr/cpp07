This project has been created as part of the 42 curriculum by alnassar.

# C++ - Module 07: C++ Templates

## Description
**C++ Module 07** introduces **Generic Programming** and **Compile-Time Polymorphism** through **Templates** in C++98.

In earlier modules, polymorphism was achieved at runtime via inheritance and virtual functions (`vptr`/`vtable`), which incurs runtime overhead (indirect pointer dereference) and requires common base classes.

Templates allow programmers to write blueprints for functions and classes that operate on **any data type** while maintaining complete compile-time type safety and zero runtime performance penalty.

---

## 📑 Summary of Exercises

| Exercise | Primary Topic | Key Deliverables | Evaluation Focus |
| :--- | :--- | :--- | :--- |
| **[ex00: Start with a few functions](ex00/)** | Function Templates | `whatever.hpp`, `main.cpp` | Generic `swap`, `min`, `max`; strict equality tie-break returning 2nd argument. |
| **[ex01: Iter](ex01/)** | Higher-Order Function Templates | `iter.hpp`, `main.cpp` | Iterating arrays of any type; supporting const and non-const arrays and instantiated function templates. |
| **[ex02: Array](ex02/)** | Class Templates & Dynamic Memory | `Array.hpp`, `main.cpp` | Generic container class; Orthodox Canonical Form; `new[]`/`delete[]`; value-initialization; bounds checking with `std::exception`. |

---

## 🛠️ Exercises Overview

### [Exercise 00: Start with a few functions](ex00/)
- **Header**: `whatever.hpp` (defined entirely in the header).
- **Function Templates**:
  - `template <typename T> void swap(T& a, T& b)`: Swaps the values of two variables of the same type without returning anything.
  - `template <typename T> const T& min(const T& a, const T& b)`: Returns the smallest value. If values are equal, **returns the second argument (`b`)**.
  - `template <typename T> const T& max(const T& a, const T& b)`: Returns the greatest value. If values are equal, **returns the second argument (`b`)**.
- **Requirements**:
  - Can be called with any type that supports comparison operators (`<`, `>`).
  - Tested with built-in types (`int`, `std::string`) and custom classes with operator overloads (`Awesome`).

### [Exercise 01: Iter](ex01/)
- **Header**: `iter.hpp`
- **Function Template**:
  - `template <typename T, typename F> void iter(T* array, const std::size_t length, F func)`
  - `template <typename T, typename F> void iter(const T* array, const std::size_t length, F func)`
- **Behavior**:
  - Takes 3 parameters: array address, array length as a `const` value, and a callable function/functor.
  - Traverses the array from index `0` to `length - 1`, invoking `func(array[i])`.
  - Works with non-const arrays (allowing element mutation when `func` takes non-const reference `T&`).
  - Works with `const` arrays (read-only traversal).
  - Supports instantiated function templates (e.g., `printElement<int>`).

### [Exercise 02: Array](ex02/)
- **Header**: `Array.hpp`
- **Class Template**: `Array<T>`
- **Behavior & Member Functions**:
  - `Array()`: Default constructor, initializes an empty array (`_elements = NULL`, `_length = 0`).
  - `Array(unsigned int n)`: Allocates dynamic memory using `new T[n]()`. Parentheses guarantee **value-initialization** (zero-initialization for primitives, default constructor for objects).
  - `Array(const Array& other)`: Copy constructor performing a **deep copy**.
  - `Array& operator=(const Array& rhs)`: Copy assignment operator with self-assignment guard, memory deallocation, and deep copy.
  - `~Array()`: Destructor freeing allocated memory with `delete[] _elements`.
  - `T& operator[](unsigned int index)`: Non-const subscript operator with boundary check; throws `std::out_of_range` (inheriting from `std::exception`) if `index >= _length`.
  - `const T& operator[](unsigned int index) const`: Const subscript operator for read-only access.
  - `unsigned int size() const`: Returns number of elements without modifying instance state.

---

## 📋 Evaluation Sheet Checklist

- [x] **Prerequisites**:
  - Compiles with `c++ -Wall -Wextra -Werror -std=c++98`.
  - No C++11 (or later) features, no Boost.
  - No C memory functions (`malloc`, `free`, `printf`).
  - No `using namespace <ns_name>` or `friend` keyword.
  - No STL containers or algorithms (`<vector>`, `<algorithm>`, etc. forbidden until Module 08).
  - All template definitions are in header files.
  - Include guards on all headers.
  - Zero memory leaks.

- [x] **Exercise 00**:
  - Files named `Makefile`, `main.cpp`, `whatever.hpp` (lowercase).
  - `swap`, `min`, `max` defined as function templates.
  - `min` and `max` return the second parameter when values are equal (verified via pointer equality `&min(eq1, eq2) == &eq2`).
  - Tested with basic types and custom classes with overloaded operators.

- [x] **Exercise 01**:
  - Files named `Makefile`, `main.cpp`, `iter.hpp` (lowercase).
  - `iter` accepts 3 parameters: array pointer, `const` length, callable function.
  - Supports both `const` and non-const arrays.
  - Supports modifying functions and instantiated function templates.
  - Tested with primitive arrays, const string arrays, and custom classes (`Awesome`).

- [x] **Exercise 02**:
  - Files named `Makefile`, `main.cpp`, `Array.hpp`.
  - `Array<T>` implements Orthodox Canonical Form.
  - Allocates with `new[]` and deallocates with `delete[]`.
  - Value-initialization via `new T[n]()`.
  - Subscript operator `operator[]` provided for both non-const and const instances.
  - Accessing invalid indices (negative numbers, index $\ge$ size) throws `std::exception`.
  - Deep copy verified: modifications to copy do not affect original.
  - Passes official 42 subject benchmark (`MAX_VAL = 750` with mirror verification).

---

## 🚀 Compilation & Running

Each exercise contains its own independent `Makefile`:

```bash
# Exercise 00
cd ex00 && make
./whatever

# Exercise 01
cd ../ex01 && make
./iter

# Exercise 02
cd ../ex02 && make
./array
```
