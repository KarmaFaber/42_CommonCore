# pipex

A systems programming project in C that recreates the UNIX inter-process communication mechanism of shell pipelines (`< file1 cmd1 | cmd2 > file2`).

---

## 📌 Technical Scope & Subject Requirements

* **Program Signature**: `./pipex file1 cmd1 cmd2 file2`.
* **Core Functionality**:

  * Emulates the exact behavior of `< file1 cmd1 | cmd2 > file2`.
  * Takes input from `file1`, feeds it to `cmd1`, redirects stdout of `cmd1` to stdin of `cmd2` via an IPC unidirectional data channel, and saves the output into `file2`.
* **System Call Primitives Allowed**: `open`, `close`, `read`, `write`, `pipe`, `fork`, `dup`, `dup2`, `execve`, `wait`, `waitpid`, `unlink`, `access`, `perror`, `strerror`.
* **Robustness & Error Handling**:

  * Matches shell exit statuses and error outputs for inaccessible/missing input files (`ENOENT`, `EACCES`), nonexistent commands, and permission issues.
  * Zero memory leaks and strict heap allocation tracking.
  * Zero crash tolerance (`SIGSEGV`, `SIGBUS`, double free).

---

## 📐 Architecture & System Mechanics

### Process Forking & Pipeline Flow

The implementation manages process separation and stream redirection through POSIX kernel interfaces:

```text
[ file1 ] ---> stdin ---> [ Child 1: cmd1 ] ---> stdout ---> [ pipe[1] ]
                                                               |
                                                               | (IPC pipe)
                                                               v
[ file2 ] <--- stdout <--- [ Child 2: cmd2 ] <--- stdin  <--- [ pipe[0] ]
```

### Key Learnings & Engineering Concepts

* **Inter-Process Communication (`pipe`)**: Creation of unidirectional data channels providing standard file descriptors (`pipefd[0]` for read, `pipefd[1]` for write).
* **Stream Duplication (`dup2`)**: Redirecting `stdin` (`STDIN_FILENO`) and `stdout` (`STDOUT_FILENO`) to respective file and pipe descriptors before executing programs.
* **Descriptor Lifecycle Management**: Closing unused read/write ends in parent and child processes to ensure EOF propagates correctly through the pipeline and avoid descriptor leaks.
* **Environment Parsing & `execve`**: Resolving binary absolute paths by traversing the system `PATH` variable, managing argument vectors (`argv`), and executing commands in isolated child address spaces.
* **Process Synchronization (`waitpid`)**: Synchronizing process lifecycle to capture child termination statuses and avoid zombie processes.

---

## 🛠️ Instructions & Compilation

### Build

Compile the binary using the provided `Makefile`:

```bash
make
```

### Usage Examples

Equivalent shell syntax execution:

Bash

```bash
# Equivalent to: < infile ls -l | wc -l > outfile
./pipex infile "ls -l" "wc -l" outfile

# Equivalent to: < infile grep test | wc -w > outfile
./pipex infile "grep test" "wc -w" outfile
```

## 📚 Resources & Integrity

* **POSIX Standard Interfaces**: Built against IEEE Std 1003.1 specifications for `pipe(2)`, `fork(2)`, `dup2(2)`, and `execve(2)`.
* **AI Disclosure**: AI tools were utilized exclusively as sounding boards to define test suites for permission edge cases (non-readable infiles, non-writable outfiles, invalid command paths). Process pipeline architecture, descriptor cleanup routines, and code implementation were produced and verified directly.
