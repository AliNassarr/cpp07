# 📚 CPP Module 07: Complete Study Guide & Peer Evaluation Defense

This study guide is designed to give you a complete, crystal-clear understanding of **C++ Module 07 (C++ Templates)**, ace your 42 peer evaluation defense, and handle any live code modifications requested by evaluators.

---

## 📑 Table of Contents
1. [The Big Picture: What are Templates?](#1-the-big-picture-what-are-templates)
2. [Compile-Time Polymorphism vs Run-Time Polymorphism](#2-compile-time-polymorphism-vs-run-time-polymorphism)
3. [Why Must Template Definitions Live in Header Files?](#3-why-must-template-definitions-live-in-header-files)
4. [Exercise 00: Function Templates (`swap`, `min`, `max`)](#4-exercise-00-function-templates-swap-min-max)
5. [Exercise 01: Iter (`iter`)](#5-exercise-01-iter-iter)
6. [Exercise 02: Class Template (`Array<T>`)](#6-exercise-02-class-template-arrayt)
7. [Top Peer Evaluation Defense Questions & Answers](#7-top-peer-evaluation-defense-questions--answers)
8. [Live Code Modification Practice (Subject Chapter VII)](#8-live-code-modification-practice-subject-chapter-vii)

---

## 1. The Big Picture: What are Templates?

In C, if you wanted to write a function to swap two integers and another to swap two floats, you had to write two separate functions:
```c
void swap_int(int* a, int* b) { int t = *a; *a = *b; *b = t; }
void swap_float(float* a, float* b) { float t = *a; *a = *b; *b = t; }
```
Alternatively, C programmers used `void*` and `memcpy`:
```c
void swap(void* a, void* b, size_t size); // Slow, completely strips type safety!
```

### The C++ Solution: Templates
In C++, a **template** is a blueprint from which the compiler generates concrete, type-safe functions or classes at compile time.
```cpp
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}
```
When you call `swap(x, y)` with integers, the compiler automatically generates a concrete function `swap(int&, int&)`. When called with `std::string`, it generates `swap(std::string&, std::string&)`.

**Key Advantages:**
1. **Zero Code Duplication**: One blueprint works for all types.
2. **Total Type Safety**: Full compiler type checking; no void pointers or unsafe casts.
3. **Zero Runtime Overhead**: No virtual dispatch table (`vtable`); code is generated directly by the compiler and can be inlined for maximum speed.

---

## 2. Compile-Time Polymorphism vs Run-Time Polymorphism

| Feature | Run-Time Polymorphism (Module 04–06) | Compile-Time Polymorphism (Module 07) |
| :--- | :--- | :--- |
| **Mechanism** | Virtual functions, inheritance, base pointers | Function & Class Templates |
| **When Resolved** | At **Runtime** via `vptr` and `vtable` | At **Compile time** via template instantiation |
| **Performance** | Small penalty (indirect pointer dereference) | **Zero penalty** (direct function calls, inlineable) |
| **Flexibility** | Types must inherit from a common `Base` class | Types do **not** need inheritance; they only need to support required operations (e.g. `<`, `>`) |
| **Binary Size** | Fixed size | Code bloat possible (compiler generates separate code for each type `T`) |

---

## 3. Why Must Template Definitions Live in Header Files?

In standard C++, regular functions have declarations in `.hpp` and definitions in `.cpp`:
```
main.cpp ---> compiles to main.o  \
                                   ---> Linker binds them into executable
foo.cpp  ---> compiles to foo.o   /
```

### Why does this fail with Templates?
A template is **not executable code**—it is only a blueprint. 

1. When `foo.cpp` is compiled into `foo.o`, if it only contains `template <typename T> void func(T val) { ... }`, the compiler **does not generate any machine instructions** because it doesn't know what types `T` will be needed!
2. When `main.cpp` calls `func(42)`, the compiler sees the declaration of `func<int>`, but without the definition in the header, it cannot generate the code for `func<int>`. It leaves an external reference for the linker.
3. At link time, the linker looks for `func<int>` in `foo.o`, but finds nothing $\rightarrow$ **`undefined reference to void func<int>(int)`** linker error!

> [!IMPORTANT]
> Because the compiler must instantiate the template at the exact point of invocation, the **full implementation of templates must be visible in the header file** (or in an included `.tpp` file).

---

## 4. Exercise 00: Function Templates (`swap`, `min`, `max`)

### 1. `swap`
```cpp
template <typename T>
void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}
```
- Parameters are passed by **reference (`T&`)** so that modifications mutate the caller's actual variables.
- Requires `T` to have an accessible copy constructor and assignment operator.

### 2. `min` and `max` (The Equality Tie-Break Rule)
The 42 subject explicitly states:
> *"min: Compares the two values passed as parameters and returns the smallest one. **If they are equal, it returns the second one.**"*
> *"max: Compares the two values passed as parameters and returns the greatest one. **If they are equal, it returns the second one.**"*

```cpp
template <typename T>
const T& min(const T& a, const T& b)
{
    return (a < b) ? a : b;
}

template <typename T>
const T& max(const T& a, const T& b)
{
    return (a > b) ? a : b;
}
```

#### Why does this return the second one on equality?
- If `a == b`, then `a < b` is **`false`**. The ternary operator `(false) ? a : b` evaluates to **`b`** (the second parameter).
- If `a == b`, then `a > b` is **`false`**. The ternary operator `(false) ? a : b` evaluates to **`b`** (the second parameter).
- Both return `const T&` to avoid expensive copies of large objects.

### Proof of Equality Tie-Break
In `ex00/main.cpp`, we prove this using memory addresses:
```cpp
int eq1 = 42;
int eq2 = 42;
assert(&::min(eq1, eq2) == &eq2); // Evaluates to TRUE!
```

---

## 5. Exercise 01: Iter (`iter`)

### Subject Requirements
1. First parameter: address of an array.
2. Second parameter: length of the array, passed as a `const` value.
3. Third parameter: a function called on every element.
4. Must work with const and non-const arrays.
5. The third parameter can be an instantiated function template.

### The Implementation
```cpp
template <typename T, typename F>
void iter(T* array, const std::size_t length, F func)
{
    if (!array)
        return;
    for (std::size_t i = 0; i < length; ++i)
        func(array[i]);
}

template <typename T, typename F>
void iter(const T* array, const std::size_t length, F func)
{
    if (!array)
        return;
    for (std::size_t i = 0; i < length; ++i)
        func(array[i]);
}
```

### Why use `typename F` instead of `void (*func)(T&)`?
If you define `iter` with a rigid function pointer:
```cpp
// Flawed approach:
template <typename T>
void iter(T* array, const std::size_t length, void (*func)(T&));
```
This fails when:
1. `func` takes its parameter by `const T&` (e.g. a printing function) on a non-const array.
2. `func` returns a value (e.g. `int func(T&)` or `bool func(T&)`).
3. `func` is a functor (function object).

By using `template <typename T, typename F>`, `F` deduces the exact callable type (function pointer, function template instantiation `print<int>`, functor) cleanly and safely!

---

## 6. Exercise 02: Class Template (`Array<T>`)

### 1. Orthodox Canonical Form (OCF)
A class template managing heap memory must implement all 4 OCF member functions:
1. **Default Constructor**:
   ```cpp
   Array() : _elements(NULL), _length(0) {}
   ```
2. **Copy Constructor**:
   ```cpp
   Array(const Array& other)
       : _elements(other._length > 0 ? new T[other._length]() : NULL), _length(other._length)
   {
       for (unsigned int i = 0; i < _length; ++i)
           _elements[i] = other._elements[i];
   }
   ```
3. **Copy Assignment Operator**:
   ```cpp
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
   ```
   > [!TIP]
   > Notice that `newElements` is allocated **before** `delete[] _elements`. If allocation throws an `std::bad_alloc` exception, the existing array remains completely uncorrupted (Strong Exception Guarantee).
4. **Destructor**:
   ```cpp
   ~Array()
   {
       delete[] _elements;
   }
   ```
   `delete[] NULL` is completely safe and a standard no-op in C++.

### 2. Value-Initialization: `new T[n]()`
The subject gives an explicit hint:
> *"Tip: Try to compile `int * a = new int();` then display `*a`."*

- In C++, `new int` leaves the memory **uninitialized** (filled with random garbage bits).
- `new int()` with parentheses **value-initializes** the primitive, setting it to `0`.
- In `Array.hpp`, using `new T[n]()` guarantees that primitive types (`int`, `float`, `char`) are zeroed, and class instances have their default constructors called!

### 3. Subscript Operator: Non-Const vs Const
We must provide **two** overloads of `operator[]`:
```cpp
// Non-const: allows modifying elements (arr[0] = 42)
T& operator[](unsigned int index)
{
    if (index >= _length)
        throw std::out_of_range("Array index out of range");
    return _elements[index];
}

// Const: allows reading elements from const Array instances
const T& operator[](unsigned int index) const
{
    if (index >= _length)
        throw std::out_of_range("Array index out of range");
    return _elements[index];
}
```

#### Why `unsigned int index`?
- Because an array length cannot be negative.
- If a caller passes a negative number like `numbers[-2]`:
  In C++, `-2` converts implicitly to an unsigned integer (e.g., `4294967294`). Because `4294967294 >= _length`, the `if (index >= _length)` check triggers immediately and throws `std::out_of_range`!

---

## 7. Top Peer Evaluation Defense Questions & Answers

### Q1: What is the difference between `typename` and `class` in `template <typename T>`?
**Answer**: In template parameter lists, `template <typename T>` and `template <class T>` are **100% synonymous and identical** to the compiler. `typename` was introduced later in C++ standardization to make it clear that `T` can be any type (including primitive types like `int` or `char`), not just a `class`.

### Q2: Why can't we put template definitions in a `.cpp` file?
**Answer**: Because C++ compiles each `.cpp` file as an independent Translation Unit. The compiler only generates machine code for a template when it is instantiated with a concrete type (e.g. `Array<int>`). If the definition is in a separate `.cpp` file, other translation units only see the declaration, so the compiler cannot generate the code, leading to an **undefined reference** error at link time.

### Q3: What happens when `min(a, b)` is called on two equal values?
**Answer**: Our implementation returns the second argument `b`:
```cpp
return (a < b) ? a : b;
```
When `a == b`, `(a < b)` evaluates to `false`, causing the ternary operator to return `b`. This strictly satisfies the subject rule.

### Q4: Why did you provide both `const` and non-const overloads for `operator[]` in `Array`?
**Answer**: If only non-const `T& operator[](unsigned int)` existed, any `const Array<T>` instance could not have its elements accessed—the compiler would reject calls on const objects. If only `const T& operator[](unsigned int) const` existed, callers could never modify array elements (`arr[0] = 10` would fail to compile). Providing both overloads ensures const-correctness.

### Q5: How does your `Array` prevent memory leaks during self-assignment (`a = a`)?
**Answer**: The assignment operator starts with a self-assignment check: `if (this != &rhs)`. If an instance is assigned to itself, the function immediately returns `*this` without deleting or reallocating memory.

---

## 8. Live Code Modification Practice (Subject Chapter VII)

Chapter VII of the subject states that an evaluator may ask for a brief live modification during defense. Here are the most common scenarios:

### Scenario 1: Add an `.empty()` method to `Array<T>`
```cpp
bool empty() const
{
    return _length == 0;
}
```

### Scenario 2: Add an `operator<<` stream overload for `Array<T>`
Add this outside the class template:
```cpp
template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& arr)
{
    os << "[ ";
    for (unsigned int i = 0; i < arr.size(); ++i)
    {
        os << arr[i];
        if (i + 1 < arr.size())
            os << ", ";
    }
    os << " ]";
    return os;
}
```

### Scenario 3: Change `min` / `max` to return the first argument instead of the second on equality
```cpp
// Returns first on equality:
return (b < a) ? b : a; // if equal, b < a is false -> returns a
```

### Scenario 4: Add a `.fill(const T& val)` method to `Array<T>`
```cpp
void fill(const T& val)
{
    for (unsigned int i = 0; i < _length; ++i)
        _elements[i] = val;
}
```
