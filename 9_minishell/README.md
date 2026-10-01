# Minishell

A POSIX-compliant UNIX command interpreter built in C. The project models process isolation, inter-process communication (IPC pipelines), file descriptor duplication, signal dispatching, environment table management, and tokenization without relying on high-level runtime parsers.

---

## 📌 Technical Scope & Subject Requirements

* **Interactive Prompt & History**: Reads interactive user input via GNU `readline` and logs non-empty commands into traversal history (`add_history`).
* **Execution & Binary Resolution**:

  * Locates target executables by inspecting the `PATH` environment variable or direct paths (absolute `/` or relative `./`).
  * Executes external binaries in isolated address spaces using `fork` and `execve`.
* **Built-in Commands**: Custom implementations of core shell utilities:

  * `echo` (with `-n` flag).
  * `cd` (handles relative and absolute paths, updates `PWD` / `OLDPWD`).
  * `pwd` (prints current working directory).
  * `export` (modifies/adds environment variables).
  * `unset` (removes environment keys).
  * `env` (prints active environment table).
  * `exit` (clean shell termination with deterministic status propagation).
* **I/O Redirections & Pipelines**:

  * Input redirection: `< file`.
  * Output truncation: `> file` (`O_TRUNC`).
  * Output appending: `>> file` (`O_APPEND`).
  * Heredoc: `<< DELIMITER` (reads input stream until boundary token without updating history).
  * Pipelines: `cmd1 | cmd2 | ... | cmdN` (connects stdout of command $i$ to stdin of command $i+1$ via anonymous pipes).
* **Quoting & Variable Expansions**:

  * Single quotes (`'...'`): Suppresses evaluation of all meta-characters.
  * Double quotes (`"..."`): Suppresses meta-characters while enabling variable expansion (`$`).
  * Parameter expansion: Resolves `$VAR` environment variables and `$?` (exit status of the most recent executed pipeline).
* **Signal Handling**:

  * Emulates Bash behavior for `ctrl-C` (SIGINT), `ctrl-D` (EOF), and `ctrl-\` (SIGQUIT).
  * **Strict Constraint**: Only a single global integer variable is permitted, exclusively used to store the received signal code, maintaining decoupling from data structures.
* **Memory & Integrity**: Zero memory leaks across parsing/execution cycles (excluding internal `readline` allocations) and zero crash tolerance under malformed input.

---

## 📐 Systems Architecture & Execution Mechanics

### 1. Command Processing Pipeline

The core loop converts raw user input into an Abstract Syntax Tree (AST) or tokenized command array before executing:

```text
[ readline Prompt ] ──► [ Lexer / Tokenizer ] ──► [ State Machine Parser ]
                                                  (Words, Quotes,          (Validates Syntax & Pipes, Redirs)
                                                   Orders AST/Nodes)
                                                           │
                                                           ▼
                                                  [ Expansion Engine ]
                                                  ($VAR, $?, Quotes)
                                                           │
                                                           ▼
                                                  [ Execution Engine ]
                                                  (Built-ins vs Fork)
                                                           │
                         ┌─────────────────────────┬────────┴─────────────────────────┐
                         ▼                         ▼                                  ▼
                [ Single Built-in ]        [ Pipeline Fork ]                [ Child Processes ]
                Executes directly          pipe() / dup2()                 execve() / waitpid()
                in parent (e.g., cd)      stream plumbing                   exit status handling
```

### 2. IPC Plumbing & Descriptor Sanitation

* **Pipeline Multiplexing**: Iteratively creates `pipe(fd)` channels for $N$ commands. In each child, `dup2` maps the appropriate read/write file descriptors onto `STDIN_FILENO` and `STDOUT_FILENO`.
* **Deterministic File Descriptor Closure**: Systematically closes both ends of unused pipe descriptors in parent and child processes to ensure EOF propagates correctly and avoid system-level descriptor leaks.
* **Process Lifecycle Synchronization**: Parent process executes a non-preemptive `waitpid` cascade, capturing process exit codes ($WIFEXITED$, $WEXITSTATUS$, $WTERMSIG$) to populate `$?` accurately.

### 3. Safe Signal Propagation

Signal listeners configured via `sigaction` or `signal` distinguish between interactive prompt states, heredoc capturing, and child process blocking:

* In interactive mode, `SIGINT` clears the line and redraws the prompt.
* During child execution, signals propagate to the child process group without re-triggering parent prompt re-renders.

---

## 🛠 Instructions & Build

### Prerequisites

* Linux / POSIX development environment.
* Standard C compiler (`gcc` or `clang`).
* GNU Readline library (`libreadline-dev`).

### Compilation

```bash
make
```

### Execution

```bash
./minishell
```

### Example Usage

```bash
minishell$ export TARGET=world
minishell$ echo "Hello $TARGET" | cat -e
Hello world$
minishell$ < Makefile grep NAME > output.txt
minishell$ cat output.txt
NAME = minishell
minishell$ echo $?
0
```

## 🎯 Target Relevance: C/C++ Systems & Industrial Software

* **Operating System Kernel Interfaces**: Direct hands-on use of fundamental POSIX system calls (`fork`, `execve`, `waitpid`, `pipe`, `dup2`, `sigaction`), mirroring the core architecture of process managers, Linux daemons, and embedded system supervisory layers.
* **Resource Boundary Defense & Lifecycle Sanitation**: Strict tracking of heap structures and dynamic arrays per prompt cycle, ensuring non-leaking, crash-resilient runtimes for continuous industrial equipment operation.
* **Low-Level Stream Management**: Precise control of byte streams and file descriptors under asynchronous interrupts, directly applicable to industrial communication gateways and device telemetry pipes.

## Collaborators:
- [nataiuca](https://github.com/nataiuca)
- [KarmaFaber](https://github.com/KarmaFaber)

## 📚 Resources & Integrity

* **POSIX Standard Reference**: IEEE Std 1003.1 for POSIX shell execution semantics, process lifecycle controls, and environment manipulation.
* **AI Disclosure**: AI tooling was used as an analytical peer to review edge-case test suites (nested quoting boundaries, pipeline EOF deadlock conditions, and permission error handling). Core parsing logic, pipe orchestration, signal handlers, and execution structures were engineered and debugged directly.
