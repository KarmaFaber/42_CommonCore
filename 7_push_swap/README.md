# push_swap

An algorithmic optimization project written in C designed to sort an arbitrary sequence of 32-bit signed integers using two stacks (`a` and `b`) and a strictly limited set of stack-manipulation instructions, achieving the lowest possible operation count.

---

## 📌 Technical Scope & Subject Requirements

* **Program Signature**: `./push_swap <list_of_integers>`.
* **Stack State & Target Conditions**:

  * Stack `a` is initialized with unique negative and/or positive integers (first parameter at the top).
  * Stack `b` starts completely empty.
  * Program terminates with stack `a` fully sorted in ascending order and stack `b` empty.
* **Allowed Instruction Set**:

  * Push: `pa`, `pb` (transfers top element between stacks).
  * Swap: `sa`, `sb`, `ss` (swaps top two elements).
  * Rotate: `ra`, `rb`, `rr` (shifts all elements up by 1; head becomes tail).
  * Reverse Rotate: `rra`, `rrb`, `rrr` (shifts all elements down by 1; tail becomes head).
* **Input Parsing & Error Handling**:

  * Detects and rejects non-integer inputs, values exceeding 32-bit limits (`INT_MIN` / `INT_MAX`), duplicate values, and empty parameter strings.
  * Outputs `Error\n` to `stderr` and exits cleanly upon invalid input.
  * Silent execution (returns prompt with zero instructions) if input is empty or already sorted.
* **Optimization Benchmarks**:

  * 100 random integers: $< 700$ operations.
  * 500 random integers: $\le 5500$ operations.
* **Memory & Systems Constraints**: Zero memory leaks (`valgrind` clean), no global variables, no segfaults or undefined behavior under boundary states.

---

## 📐 Architecture & Algorithmic Strategy

### 1. Data Representation & Stack Mechanics

The application maps stack abstractions via contiguous circular buffers or doubly linked list nodes (`t_stack`), storing numeric values alongside normalized index ranks ($0$ to $N - 1$):

* **Coordinate Compression / Indexing**: Raw values are pre-indexed according to their sorted target positions, enabling constant-time relative evaluations and bitwise masks without mutating the original integer bounds.
* **Double Rotation Cost Optimization**: Evaluation logic inspects simultaneous shift opportunities (`rr`, `rrr`) to halve operational overhead when aligning targets in both stacks concurrently.

```text
Input: [ 42, -5, 128, 0 ]

│

▼ (Parse, Overflow & Duplicate Check)

Array: [-5, 0, 42, 128]  -->  Normalized Target Ranks: [0, 1, 2, 3]

│

▼

Stack A (Top -> Bottom): [2, 0, 3, 1] | Stack B: []

│

▼ (Cost-Driven Execution / Chunk Partitioning)

Sequential Instruction Dispatch (pb, sa, rr, pa...)

│

▼

Stack A: [-5, 0, 42, 128] (Sorted)    | Stack B: []
```

### 2. Algorithmic Decisions by Set Size

* **Small Sets ($N \le 5$)**: Deterministic decision trees (hardcoded state checks for $N=3$; minimum-extraction pivots for $N=5$) guaranteeing absolute minimum instruction counts ($\le 3$ ops for 3 items, $\le 12$ ops for 5 items).
* **Medium to Large Sets ($N = 100$ to $500$)**:

  * **Greedy / Chunk Sort (Turk Algorithm variant)**: Dynamic cost-benefit calculation per element evaluating the cheapest combination of single and dual rotations required to place a node into its optimal target position.
  * **Bitwise Radix Sort (Alternative Baseline)**: $O(b \cdot N)$ bitwise partitioning passing each bit position from stack `a` to stack `b` via binary masks (`>> bit & 1`), providing deterministic bounds on arbitrary distributions.

---

## 🛠️️ Instructions & Build

### Compilation

Compile the binary using the strict project `Makefile`:

```bash
make
```

### Execution

Run directly by passing space-separated integers or quoted sequences:

Bash

```bash
# Direct parameters
./push_swap 2 1 3 6 5 8

# Quoted argument string
ARG="4 67 3 87 23"; ./push_swap $ARG

# Measure instruction count against benchmarks
ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l
```

## 🎯 Target Relevance: C/C++ Systems & Industrial Software

* **Resource-Constrained Algorithm Optimization**: Demonstrates the capability to sort arbitrary data under strict operation and execution-step budgets, directly transferable to hardware control loops, telemetry queuing, and memory-constrained microcontrollers.
* **Defensive Input Parsing**: Robust validation of external inputs against integer overflow thresholds (`strtol`/`ft_atoi` limit verification) preventing arithmetic wraparound and buffer vulnerabilities in low-level drivers.
* **Deterministic Execution & Memory Sanitation**: Zero heap fragmentation or leak footprint, ensuring deterministic behavior in continuous industrial software runtimes.

## 📚 Resources & Integrity

* **Complexity Benchmarks**: Algorithm evaluation based on asymptotic time complexity analysis ($O(N \log N)$ average cases vs. $O(N^2)$ worst-case costs).
* **AI Tool Disclosure**: AI tooling was employed exclusively to generate diverse permutation test vectors and fuzzing harnesses for boundary conditions (`INT_MIN`, `INT_MAX`, reverse-sorted datasets). Algorithm design, linked list/stack memory logic, parsing modules, and Makefile rules were constructed and verified directly
