_This project has been created as part of the 42 curriculum by asadik._

## Description

This project implements the classic Dining Philosophers problem in C. Each philosopher runs in its own thread, and each fork is represented by a mutex.

Philosopher `i` tries to take fork `i` (left) and fork `i+1` (right). To reduce race conditions, even-numbered threads start with an initial sleep. To avoid deadlocks when the number of philosophers is odd, each philosopher spends some time thinking after eating. Mutexes are also used for printing, to avoid mixed output, and for death checks, to prevent a philosopher from starting to eat after the simulation has ended.

## Build

```bash
cd Philo
make
```

Use `make debug` to compile with the `-g` flag. All other standard make rules apply.

## Resources

- https://www.geeksforgeeks.org/c/multithreading-in-c/
- Prior experience with multithreaded programming in Rust

This readme was proofread and corrected with the help of AI.