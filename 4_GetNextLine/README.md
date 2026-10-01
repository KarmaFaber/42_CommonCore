# get_next_line

A memory-efficient C routine designed to read and return a line terminated by a newline (`\n`) or EOF from a given file descriptor (`fd`) across successive function calls.

---

## 📌 Technical Scope & Subject Requirements

* **Function Signature**: `char *get_next_line(int fd);`.
* **Allowed System Calls & Functions**: `read`, `malloc`, `free` (explicitly prohibiting `lseek` and global variables).
* **Memory & Stream Integrity**:

  * Returns the line read including the trailing `\n` (unless reaching EOF without a final newline).
  * Returns `NULL` when reaching EOF or if a read error occurs.
  * Fully independent of static input boundaries: compiled with a variable `-D BUFFER_SIZE=n` flag, supporting edge cases from `BUFFER_SIZE=1` to `BUFFER_SIZE=10000000` without heap exhaustion or memory leaks.
  * Standard stream compatibility: seamlessly reads from regular disk files, pipes, and standard input (`stdin`).

---

## 📐 Architecture & Key Learnings

### 1. State Persistence via Static Variables

In C, local variables lose their state upon returning from a function frame. `get_next_line` leverages a **static pointer (`static char *stash`)** to preserve remaining unread bytes from previous `read()` cycles across successive invocations.

```text
[ read(fd, buf, BUFFER_SIZE) ] ---> [ Append to Static Stash ]
                                      |
                                      v
                               [ Scan for '\n' or EOF ]
                                      /
                                     /
                         Found '\n'          No '\n' & EOF
                              /                    /
                             /                    /
              [ Extract Line: start -> '\n' ]    [ Extract remaining bytes ]
              [ Update Stash: '\n'+1 -> end ]    [ Free Stash & set to NULL ]
                             \                    /
                              \                  /
                               v                v
                            [ Return allocated line ]
```

### 2. Algorithmic Decisions & Edge Handling

* **Incremental Buffering**: Reads only the necessary blocks until a newline delimiter is detected, avoiding full-file buffering into memory.
* **Zero Leak Policy**: If a read error occurs mid-stream (e.g., negative return value from `read()`), the internal stash is systematically freed and pointed to `NULL` to prevent dangling references or memory leaks.
* **Clean String Slicing**: Custom string utilities (`ft_strlen`, `ft_strchr`, `ft_strjoin`, `ft_substr`) handle dynamic reallocation without relying on external libraries (`libft` is forbidden).

---

## 🛠️ Instructions & Compilation

Include `get_next_line.c`, `get_next_line_utils.c`, and the header `get_next_line.h` into your target build.

### Compilation Example

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl_demo
```

### Basic Usage Loop

C

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int   fd = open("sample.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## 📚 Resources & Integrity

POSIX Specification: Built around POSIX file I/O operations defined in `<unistd.h>` (read(2) semantics and file offset lifecycles).

AI Tool Disclosure: AI-assisted prompts were used exclusively for stress-testing boundary conditions (zero-length files, files without trailing newlines, single-byte buffer limits). Algorithm design, memory deallocation chains, and pointer arithmetic were authored and verified directly
