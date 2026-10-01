# C++ Modules (CPP 00 - 09)

*A progressive systems-engineering curriculum covering Object-Oriented Programming (OOP) rigor, manual resource lifecycles (RAII), explicit type casting, generic templates, and STL container efficiency under C++98 standards.*

---

## 📌 Technical Standards & Toolchain

* **Standard**: C++98 / C++03 compliant (`-std=c++98`).
* **Compiler Flags**: Strict enforcement of `-Wall -Wextra -Werror`.
* **Zero Leak Policy**: Verified allocation tracking via `valgrind --leak-check=full` to ensure complete absence of heap leaks or uninitialized memory references.
* **Paradigm**: Direct resource control without reliance on post-C++11 smart pointers or garbage collection runtimes.

---

## 📐 Architecture & Module Breakdown

### 1. Object Lifecycle & Polymorphism (CPP 00 – 04)

* **Orthodox Canonical Form**: Explicit implementation of default constructors, copy constructors, copy assignment operators (`operator=`), and destructors to prevent shallow-copy faults and dynamic resource aliasing.
* **Memory & References**: Pointer arithmetic vs. reference binding semantics, deep copying strategies, and strict const-correctness.
* **Polymorphism**: Compile-time function/operator overloading vs. runtime dynamic dispatch through virtual method tables (`vtable`) and pure abstract interfaces (`virtual ~Base() = 0`).

### 2. Defensive Control & Type Safety (CPP 05 – 08)

* **Exception Architecture**: Hierarchical exception design (`std::exception`), stack unwinding safety, and nested error recovery across hardware/system failure boundaries.
* **C++ Cast Hierarchy**: Elimination of unsafe C-style casting in favor of explicit semantics:

  * `static_cast`: Well-defined implicit conversions and compile-time upcasts.
  * `dynamic_cast`: Safe runtime downcasting within polymorphic class hierarchies using RTTI.
  * `reinterpret_cast`: Low-level reinterpretation of raw binary bit-patterns and memory buffers (hardware address mapping).
  * `const_cast`: Explicit manipulation of volatile and constant cv-qualifiers.
* **Generic Programming**: Type-agnostic abstractions via function templates and class templates.

### 3. STL & Algorithmic Complexity (CPP 09)

Practical application of the Standard Template Library adhering to strict asymptotic complexity constraints ($O(N \log N)$ thresholds):

* **Bitcoin Exchange (`std::map`)**: Time-series database lookups and date-stamped rate queries executed in logarithmic lookup time ($O(\log N)$).
* **Reverse Polish Notation (`std::stack`)**: Linear evaluation of postfix mathematical expressions via LIFO operational queues.
* **PmergeMe (Ford-Johnson Merge-Insertion Sort)**: Dual-container benchmarking comparing insertion/merge traversal overhead between contiguous memory (`std::vector`) and double-ended chunked queues (`std::deque`).

---

## 🛠️ Build & Verification

Each module folder contains an independent build configuration:

```bash
# Navigate to any exercise directory
cd CPP09/ex00

# Compile with strict C++98 standard
make

# Run binary
./btc input.txt
```

## 🎯 Target Relevance: Embedded, Systems & Industrial Software

* **Deterministic Resource Management (RAII)**: Clean binding of hardware contexts, sockets, and heap blocks to object scope lifetimes, essential for fault-intolerant device control.
* **Hardware-Level Type Safety**: Granular bitwise reinterpretation via `reinterpret_cast` mirrors raw register manipulation and low-level peripheral buffer decoding.
* **Template Metaprogramming**: Efficient generic abstractions with zero runtime virtual table overhead.
