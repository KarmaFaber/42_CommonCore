# Philosophers

A concurrent systems programming project in C solving Edsger Dijkstra's classic Dining Philosophers problem. The implementation models thread synchronization, shared resource contention, deadlock avoidance, and strict timing constraints under POSIX threads (`pthreads`) and mutual exclusion locks (`mutexes`).

---

## 📌 Technical Scope & Subject Requirements

* **Execution Interface**:

  ```bash
  ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
  ```

*(Times specified in milliseconds; meal quota is optional)*.

* **Concurrency Model**:

  * One thread per philosopher (`pthread_create`).
  * One fork placed between each pair of philosophers, protected by a dedicated mutex lock (`pthread_mutex_t`) to prevent state corruption and simultaneous resource grabs.
* **Deterministic Logging**:

  * Formatted output: `<timestamp_in_ms> <X> <action>` where actions are: `has taken a fork`, `is eating`, `is sleeping`, `is thinking`, or `died`.
  * Atomic logging enforced via a dedicated write mutex to prevent scrambled or interleaved stdout streams.
  * Maximum latency of $\le 10\text{ ms}$ between a philosopher's starvation death and the log event emission.
* **System Constraints**:

  * Zero data races (validated via ThreadSanitizer / `-fsanitize=thread` and Helgrind).
  * Global variables strictly prohibited.
  * Zero memory leaks and graceful thread termination (`pthread_join`).

## 📐 Concurrency Architecture & Engineering Decisions

### 1. Synchronization & Deadlock Prevention

A naive implementation where all threads simultaneously grab their left fork first causes a circular wait condition (deadlock):

```text
       [ Resource Contention Loop ]
         Fork 1 <--- Philo 1 ---> Fork 2
            ^                      |
            |                      v
         Fork N <--- Philo N <--- Philo 2
```

To eliminate circular wait and starvation:

* **Asymmetric Resource Acquisition**: Even-indexed philosophers acquire the right fork then the left, while odd-indexed philosophers acquire the left then the right.
* **Staggered Routine Starts**: Micro-delays (`usleep`) or staggered thread dispatch prevent simultaneous initialization collisions.
* **Single Philosopher Corner Case**: Handled explicitly; when $N = 1$, the thread acquires the single available fork, yields CPU execution, and starves predictably after `time_to_die`.

### 2. High-Precision Timing Engine

Standard `usleep()` drifts significantly on UNIX schedulers under high context-switch loads. The project implements a precise polling sleep utility:

* Combines `gettimeofday()` sampling in a tight loop with small granular slices ($500\ \mu\text{s}$).
* Ensures microsecond-level accuracy for strict state transitions (`time_to_eat`, `time_to_sleep`) without exceeding runtime tolerances.

### 3. Monitoring & Death Detection Thread

A dedicated supervisor thread continuously polls philosopher state vectors:

* Inspects atomic elapsed time since the last registered meal (`last_meal_time` protected by state mutexes) against `time_to_die`.
* Sets a global simulation shutdown flag and unlocks waiting threads cleanly upon detecting death or when all threads satisfy the optional meal quota.

## 🛠️ Build & Usage

### Prerequisites

* Linux / POSIX-compliant environment.
* Standard C compiler (`gcc` or `clang`) with POSIX thread library support.

### Compilation

Bash

```bash
cd philo
make
```

### Execution Examples

Bash

```bash
# Standard survival test (4 philosophers, will run indefinitely)
./philo 4 410 200 200

# Starvation case (philosopher 2 will die around 310ms)
./philo 4 310 200 100

# Meal count threshold test (stops when each eats 7 times)
./philo 5 800 200 200 7

# Single philosopher edge case (takes fork and dies at 800ms)
./philo 1 800 200 200
```

## 🎯 Target Relevance: C/C++ Systems & Industrial Software

* **Thread Lifecycle Management**: Direct handling of POSIX thread instantiation, parameter binding, state observation, and thread joining without high-level runtime wrappers.
* **Critical Section Isolation**: Architecture designed around fine-grained mutex granularity, avoiding thread starvation, contention bottlenecks, and race conditions.
* **Time-Constrained Real-Time Simulation**: Structuring software loops against strict deadlines, directly applicable to industrial automation, sensor telemetry readers, and embedded state machines.

## 📚 Resources & Integrity

* **POSIX Standard**: IEEE Std 1003.1 POSIX Threads Base Definitions (`pthread_create`, `pthread_mutex_lock`, `pthread_mutex_unlock`).
* **AI Tool Disclosure**: AI utilities were used to evaluate mutex locking order models and edge-case testing matrices (e.g., verifying boundary timing under high-load CPU throttling). Thread loop routines, synchronization logic, and memory safety checks were authored and tested directly
