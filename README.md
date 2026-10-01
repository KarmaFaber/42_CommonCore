# 42 Common Core — Systems, Networking & Software Engineering Portfolio

A centralized repository containing foundational and advanced software engineering projects developed within the **42 Common Core curriculum**. The portfolio highlights hands-on implementations in low-level C and C++ (C++98), POSIX kernel interfaces, network programming, event-driven concurrency, discrete rendering mathematics, and system administration.

---

## 🛠️ Quick Navigation: Flagship Projects

| Domain | Project | Stack | Key Architectural Focus | Core Technical Skills |
| :--- | :--- | :--- | :--- | :--- |
| **Networking & APIs** | [**webserv**](./14_webserv) | `C++98` `Sockets` | Non-blocking HTTP/1.1 server (RFC 7230), I/O multiplexing (`select`/`poll`/`epoll`) | Event loops, state machines, non-blocking I/O, CGI execution |
| **UNIX Internals** | [**minishell**](./9_minishell) | `C` `POSIX` | POSIX CLI command interpreter with pipelines, redirections, and process isolation | `fork`, `execve`, `dup2`, AST parsing, asynchronous signals |
| **Concurrency** | [**philosophers**](./8_philosophers) | `C` `pthreads` | Multi-threaded resource contention engine solving the Dining Philosophers problem | POSIX threads, mutexes, deadlock/race condition prevention |
| **Graphics & Sim** | [**cub3D**](./11_cub3d) | `C` `MiniLibX` | 3D raycasting engine with DDA line traversal and wall collision bounding | Trigonometry, linear algebra, raw frame buffers, matrix parsing |
| **Systems & Cloud** | [**Inception**](./13_inception) | `Docker` `DevOps` | Microservices infrastructure built from base OS images with TLS termination | Docker Compose, reverse proxy (Nginx), volume isolation |

---

## 🏛️ Systems, Networking & Infrastructure

### [webserv (C++)](./14_webserv)
*High-performance, non-blocking HTTP/1.1 server recoded from scratch without external web libraries.*
* **Architecture**: Asynchronous event loop multiplexing network sockets via `epoll`/`poll`/`select`. Implements RFC 7230 HTTP message framing and chunked transfers.
* **CGI & Process Isolation**: Dynamically spawns child processes via unidirectional pipes (`pipe`, `fork`, `execve`) to execute external scripting engines with strict timeout supervision.
* **Configuration Parser**: Modular Nginx-style token parser supporting custom routing, static delivery, file uploads (`POST`), and custom error status routing.

### [minishell (C)](./9_minishell)
*POSIX-compliant UNIX command-line interpreter emulating core Bash features.*
* **Process Lifecycle**: Command discovery via `PATH` traversal, process spawning (`fork`), binary execution (`execve`), and termination tracking (`waitpid`).
* **I/O Plumbering**: Complete stream pipeline chaining (`|`) and redirection matrix (`<`, `>`, `>>`, `<<` heredoc) using descriptor primitives (`dup2`, `pipe`).
* **Environment & Signals**: Dynamic environment variable table management with expansion rules (`$VAR`, `$?`) and isolated signal dispatching (`SIGINT`, `SIGQUIT`).

### [philosophers (C)](./8_philosophers)
*Concurrent state-machine simulation resolving shared-memory resource contention.*
* **Thread Concurrency**: Deterministic lifecycle synchronization across multiple threads using `pthread_create` and `pthread_join`.
* **Critical Section Isolation**: Fine-grained mutex locking preventing circular wait (deadlock) and resource starvation; validated with Helgrind and ThreadSanitizer.
* **Real-Time Clocks**: Microsecond polling clock mitigating scheduler drift under heavy context-switching.

### [Inception (Docker / DevOps)](./13_inception)
*Production-ready multi-container architecture running virtualized Linux microservices.*
* **Container Hardening**: Bespoke Dockerfiles built from baseline Alpine/Debian images (no ready-made images allowed).
* **Network & Storage Boundary**: Network isolation between services (Nginx, WordPress + PHP-FPM, MariaDB), volume persistence, and TLSv1.2/v1.3 cryptographic termination.

### Born2beRoot (SysAdmin / Security)
*Headless Linux server provisioning focused on operating system hardening and security auditing.*
* **Encrypted Storage**: LVM disk partitioning configured with LUKS volume-level encryption.
* **Access Control & Auditing**: Strict `sudo` command tracking, SSH endpoint restriction, AppArmor policy enforcement, and localized UFW firewall filtering.
* **Monitoring Daemon**: Automated Bash telemetry script reporting CPU usage, memory utilization, I/O rates, and active sessions scheduled via `cron`.

### NetPractice (Network Architecture)
*Modular network addressing and IP routing configuration exercises.*
* **Addressing & Subnetting**: VLSM (Variable Length Subnet Masking), IPv4 CIDR notation, and network boundary calculations.
* **Routing Topologies**: Static route mapping, default gateway declarations, and subnet partitioning across interconnected switches and routers.

---

## 🧩 Algorithms, Spatial Mathematics & Graphics

### 2D & 3D Interactive Graphics Engines
* **[cub3D (C / Raycasting)](./11_cub3d)**: Real-time 3D maze rendering engine inspired by *Wolfenstein 3D*. Features Digital Differential Analysis (DDA) grid traversal, dynamic perspective-correct wall texture mapping, directional lighting offsets, and sliding wall collision bounding.
* **[so_long (C / 2D Tile Engine)](./6_so_long)**: Lightweight 2D top-down game built with MiniLibX (X11). Incorporates recursive flood-fill pathfinding validation to verify map solvability before memory allocation, real-time sprite rendering, and non-blocking event loops.

### Algorithmic Optimization & Data Structures
* **[push_swap (C / Sorting Optimization)](./7_push_swap)**: Specialized sorting program designed to order 32-bit signed integers using two stacks (`a` and `b`) and a restricted instruction set. Employs greedy mechanical indexing and chunk-based cost evaluation to sort large datasets (100 and 500 values) within strict asymptotic operation budgets.

---

## ⚙️ Foundational C Architecture & C++ Modules

### [C++ Modules 00 to 09 (OOP & Systems Foundations)](./12_CPPs)
*Comprehensive exploration of C++ under the strict C++98 / C++03 standard (`-std=c++98`), focusing on explicit resource management without high-level automated garbage collection.*
* **Modules 00–04 (Core OOP & Memory)**: Orthodox Canonical Class Form (deep copying, assignment mechanics), pointer arithmetic vs. references, dynamic dispatch via virtual method tables (`vtable`), and pure abstract interfaces.
* **Modules 05–08 (Type Safety & Generics)**: Hierarchical exception architectures (`std::exception`), generic class/function templates, and explicit cast conversions (`static_cast`, `dynamic_cast`, `reinterpret_cast`, `const_cast`).
* **Module 09 (STL & Complexity Constraints)**: Advanced STL container design under strict time complexity constraints ($O(N \log N)$), including time-series map traversal (`std::map`), postfix evaluation (`std::stack`), and Ford-Johnson merge-insertion sorting (`std::deque`, `std::vector`).

### Foundational C Programming (Memory, Streams & Parsing)
* **[Pipex](./5_pipex)**: POSIX process redirection and IPC pipeline emulation (`< infile cmd1 | cmd2 > outfile`) managing process execution trees and file descriptor lifecycles.
* **[get_next_line](./4_GetNextLine)**: High-performance line-by-line file reader utilizing internal static buffers across variable chunk sizes (`-D BUFFER_SIZE=n`) with zero heap leaks.
* **[ft_printf](./3_printf)**: Complete re-engineering of the standard `printf` variadic output parser (`<stdarg.h>`), conversion specifiers (`cspdiuxX%`), and memory layout rendering.
* **[Libft](./1_libft)**: Low-level C utility library recreating standard `libc` memory routines (`memset`, `memcpy`, `memmove`), string parsing, dynamic allocations, and singly-linked list abstractions.

---

## 🧪 Quality Assurance & Test Suites

Dedicated verification suites constructed to enforce zero memory leaks, validate edge cases, and verify boundary limits under continuous Linux monitoring:

* **[test_parse_webserv](https://github.com/KarmaFaber/test_parse_webserv)**: Syntax and semantic stress testing framework injecting corrupted configurations and edge directives into HTTP server parsers.
* **[ft_printf_test](https://github.com/KarmaFaber/ft_printf_test)**: Differential test harness benchmarking formatting flags, pointer addresses, and integer overflows directly against system `glibc`.
* **[GetNextLine_test](https://github.com/KarmaFaber/GetNextLine_test)**: Boundary suite stressing buffer thresholds (1 byte to 10 MB), binary files, and abrupt descriptor revocations under strict `valgrind` tracing.

