# ft_printf

A custom re-implementation of the standard C `printf` library function (`libc`), focused on string parsing, format specifier dispatching, variadic argument handling (`<stdarg.h>`), and robust low-level output formatting.

---

## 📌 Technical Scope & Subject Requirements

* **Target Output**: Compiled as a static library archive named `libftprintf.a` using `ar rcs` (the use of `libtool` is strictly forbidden).
* **Buffer Management**: Operates without implementing the standard internal I/O buffering mechanism of glibc, writing output directly through low-level primitives (`write`).
* **Return Value**: Matches standard `printf` behavior by returning the exact total count of printed characters, or `-1` if a write/formatting error occurs.
* **Format Specifiers Handled**:

  * `%c`: Single ASCII character.
  * `%s`: Null-terminated character string (handles `(null)` fallback safely).
  * `%p`: Void pointer address formatted in lowercase hexadecimal preceded by the `0x` prefix (handles `(nil)` or `0x0` edge cases per OS convention).
  * `%d` / `%i`: Signed base-10 decimal integer.
  * `%u`: Unsigned base-10 decimal integer.
  * `%x`: Lowercase unsigned base-16 hexadecimal.
  * `%X`: Uppercase unsigned base-16 hexadecimal.
  * `%%`: Escaped literal percent sign.
* **Memory & Safety Constraints**: Zero dynamic memory leaks, robust edge-case validation (`INT_MIN`, `NULL` pointers, overflow protection during numeric conversions), and zero unexpected aborts or segmentation faults.

---

## 📐 Architecture & Algorithmic Design

### Variadic Processing Pipeline

The core routine iterates over the format string and dynamically extracts arguments using the standard variadic macros:

1. **`va_start`**: Initializes the argument pointer list against the initial format string parameter.
2. **Scanner / Lexer**: Sequentially parses characters until encountering a `%` delimiter. Standard text is emitted directly to standard output via `write`.
3. **Dispatcher Table**: When an escape marker `%` is reached, the subsequent character is routed through a dedicated function dispatcher to format and render the associated typed argument.
4. **`va_arg`**: Reads the data item cast to its appropriate promoted data type (`int`, `unsigned int`, `char *`, `void *`).
5. **`va_end`**: Properly cleans up the traversal pointer prior to routine termination.

```
Format String ---> [ Loop Scan ] ---> Char != '%' ---> write() | Char == '%' v [ Type-Specifier Dispatch ] |   |   |   |   |   | %c  %s  %p  %d  %u  %x ... |   |   |   |   |   | v   v   v   v   v   v [ va_arg() extraction & Base Conversion ] | v Accumulate Printed Character Count
```

### Algorithmic Decisions & Data Representation

* **Recursive & Base Converters**: Numeric conversions (`%d`, `%i`, `%u`, `%x`, `%X`, `%p`) avoid arbitrary stack buffer allocations. Integers and hexadecimal strings are processed iteratively or recursively through division/modulo pipelines, calculating exact digit lengths and writing the byte representation directly without memory fragmentation.
* **Modular Separation**: Decoupled handlers for string, character, integer, and hex printing guarantee high cohesion, clean unit testing, and ease of inclusion into foundational C libraries (`libft`).

---

## 🛠️ Instructions & Build System

### Prerequisites

* UNIX / Linux build environment.
* C toolchain (`gcc` or `clang`, `ar`, `make`).

### Compilation

Build the static library using the standard repository Makefile:

```bash
# Compiles source files and archives into libftprintf.a
make

# Clean object files
make clean

# Full rebuild
make re
```

### Integration Example

C

```c
/* main.c */
#include "ft_printf.h"

int main(void)
{
    int count;

    count = ft_printf("String: %s | Integer: %d | Hex: 0x%x\n", "Hello World", 42, 255);
    ft_printf("Total bytes printed: %d\n", count);
    return (0);
}
```

## 📚 Resources & Academic Integrity

* **POSIX / C Standard Reference**: The implementation strictly follows the IEEE Std 1003.1 / ISO C specification for variadic argument handling (`stdarg.h`) and standard `printf(3)` format resolution.
* **AI Tool Disclosure**: AI-assisted tooling was utilized strictly for reviewing edge-case test matrices (such as extreme limits with `INT_MIN`, pointer representations across distinct architectures, and verifying output formatting parity against `glibc`). Core architecture, memory boundaries, Makefile dependencies, and parsing dispatchers were engineered and validated directly.
