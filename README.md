_This project has been created as part of the 42 curriculum by asadik._

## Description

This project implements the classic Dining Philosophers problem in C. Each philosopher runs in its own thread, and each fork is represented by a mutex.

Philosopher `i` uses fork `i` (left) and fork `(i + 1) % N` (right). To strictly prevent deadlocks, the program enforces a resource hierarchy: philosophers always attempt to lock the fork with the lower memory address first. 

To reduce initial fork contention, the starting meals are staggered:
- **Even number of philosophers:** Even-indexed threads start with a brief sleep (`tt_eat / 2`).
- **Odd number of philosophers:** Threads start in three waves (even indices, odd indices, then the last philosopher) to ensure no two neighbors start together. 
Additionally, in an odd-numbered simulation, each philosopher calculates and spends a specific amount of time thinking after eating to maintain rhythm and avoid starving neighbors. 

Mutexes are also utilized for printing (to avoid mixed output) and for death checks (to instantly notify threads and prevent a philosopher from eating after the simulation has ended).

## Instructions

```bash
make
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

### Make Rules:

- make debug: Compiles with the -g flag for debugging.
- make sanitize: Compiles with the `-pthread` and `-fsanitize=thread` flags to check for data races.
- Standard rules: `all`, `clean`, `fclean`, `re.

## Resources

https://www.geeksforgeeks.org/c/multithreading-in-c/
Prior experience with multithreaded programming in Rust

This readme was proofread and corrected with the help of AI.
