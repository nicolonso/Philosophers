*This project has been created as part of the 42 curriculum by [nalfonso].*

# Philosophers

## Description

**Philosophers** is the 42 curriculum's introduction to concurrent programming.
It revisits Dijkstra's classical "dining philosophers" problem (1965): five
(or N) philosophers sit around a table, with one fork between every two
neighbours. To eat, a philosopher must hold both adjacent forks. They alternate
between thinking, eating, and sleeping. If a philosopher goes more than
`time_to_die` milliseconds without eating, they die — and the simulation must
detect it in real time.

The challenge is to coordinate the philosophers so that:

- **No deadlock.** No global stall where everyone waits forever.
- **No starvation.** Every philosopher gets to eat in bounded time.
- **No race conditions.** Shared bookkeeping (last meal, meal counter, stop
  flag) is read and written safely.
- **Death detection within ~1 ms** of `time_to_die` being exceeded.

The repository contains two implementations of the same problem:

| Folder | Primitives | Binary |
|---|---|---|
| `philo/` | POSIX threads + `pthread_mutex_t` | `philosophers` |
| `philo_bonus/` | `fork()` processes + named semaphores (`sem_open`) | `philosophers_bonus` |

The mandatory part teaches threading, mutexes, lock ordering, and
race-condition reasoning. The bonus part teaches process creation, kernel-side
synchronization with named semaphores, signal handling, and the trade-offs of
moving from shared memory to inter-process coordination.

## Instructions

### Build

The project is written in C99 and depends only on the standard C library and
POSIX threads (linked automatically in mandatory, explicitly with `-lpthread`
in bonus). It compiles with `-Wall -Wextra -Werror`.

```bash
# Mandatory
cd philo && make

# Bonus
cd philo_bonus && make
```

`make re` performs a clean rebuild; `make clean` removes the object files;
`make fclean` also removes the binary.

### Run

```
./philosophers       <nb_philo> <time_to_die> <time_to_eat> <time_to_sleep> [must_eat]
./philosophers_bonus <nb_philo> <time_to_die> <time_to_eat> <time_to_sleep> [must_eat]
```

| Argument | Type | Meaning |
|---|---|---|
| `nb_philo` | integer ≥ 1 | Number of philosophers (and forks). |
| `time_to_die` | ms | A philosopher dies if they don't start eating within this many ms of their previous meal. |
| `time_to_eat` | ms | How long a philosopher takes to eat. |
| `time_to_sleep` | ms | How long they sleep after eating. |
| `must_eat` (optional) | integer ≥ 1 | Simulation ends when every philosopher has eaten this many times. Without this argument, the simulation only ends on a death. |

### Output format

```
<timestamp_ms> <id> <state>
```

Possible states: `is thinking`, `has taken a fork`, `is eating`, `is sleeping`,
`died`. Timestamps are in milliseconds since simulation start.

### Examples

```bash
./philosophers 5 800 200 200          # 5 philos, runs forever, no deaths
./philosophers 4 410 200 200          # tight timing, survivable
./philosophers 4 310 200 100          # someone dies (eat + sleep > die)
./philosophers 1 800 200 200          # one philo, one fork → dies after ~800 ms
./philosophers 5 800 200 200 7        # silent stop after each philo eats 7 times

./philosophers_bonus 200 800 200 200 5
```

### Sanity checks

```bash
# Mandatory
valgrind --tool=helgrind   ./philosophers 5 800 200 200 3   # zero data races
valgrind --leak-check=full ./philosophers 5 800 200 200 3   # zero leaks
valgrind --leak-check=full ./philosophers 1 800 200 200     # zero leaks on death path

# Bonus
valgrind --leak-check=full ./philosophers_bonus 5 800 200 200 5
ls /dev/shm/sem.philo_*                                       # must be empty after run
```

A deeper walkthrough of every system call used and every design decision is
available in [`PHILOSOPHERS_EXPLAINED.md`](PHILOSOPHERS_EXPLAINED.md).

## Resources

### Documentation and references consulted

- 42 Lisbon **Philosophers subject PDF** — the spec.
- Linux man pages — read before each first use:
  `man 3 pthread_create`, `man 3 pthread_mutex_lock`,
  `man 3 sem_open`, `man 3 sem_wait`,
  `man 2 fork`, `man 2 waitpid`, `man 2 kill`,
  `man 2 gettimeofday`, `man 3 usleep`.
- **Operating Systems: Three Easy Pieces** by Remzi & Andrea
  Arpaci-Dusseau (free at <https://pages.cs.wisc.edu/~remzi/OSTEP/>) —
  chapters 26 (concurrency intro), 27 (threads API), 28 (locks),
  29 (lock-based data structures), 31 (semaphores), 32 (concurrency bugs).
- **Edsger Dijkstra**, *EWD-310: Hierarchical Ordering of Sequential
  Processes* (1971) — the original lock-ordering / dining-philosophers paper.
- **Wikipedia** — *Dining philosophers problem* — for a quick overview of
  the standard solutions (resource hierarchy, arbitrator, Chandy/Misra).

### Use of AI

AI assistance was used as a structured study aid throughout the project. The
work itself — typing the code, running compilation, reading errors, running
tests, and making the program work — was done by me. AI was used for the
following well-defined tasks:
