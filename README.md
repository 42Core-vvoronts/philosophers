# philosophers

Two implementations of the Dining philosophers problem:

- Thread-based implementation using mutexes
- Process-based implementation using semaphores

## Introduction

The Dining Philosophers problem is a classic synchronization problem in computer science. This project provides an implementation of the problem using multithreading and multiprocessing to simulate the behavior of philosophers dining and thinking.

## Solution Overview

To prevent deadlocks and ensure fairness, the implementation combines 3 techniques:

1. **Resource hierarchy** — Philosophers always pick the lower-indexed fork first.
2. **Asymmetric execution** — Even and odd philosophers eat in turn to reduce contention.
3. **Staggered start** — N−1 philosophers are allowed to eat in the first wave; last odd-indexed philosopher waits briefly to start a second wave.

## Testing

To test this project, I built a custom tester: [philotester🥢](https://github.com/VICXPTRV/philotester). 

## Building

To install and run the project, follow these steps:

1. Clone the repository:

   ```sh
   git clone git@github.com:42Core-vvoronts/philosophers.git
   ```
2. Navigate to the project directory:

   ```sh
   cd philosophers/mutex && make
   ```

   or

   ```sh
   cd philosophers/semaphore && make
   ```

## Usage

To run the program, use the following command:

```sh
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

Example:

```sh
./philo 1 800 200 200 # Philo should die
```
```sh
./philo 5 800 200 200 # No philo should die
```
```sh
./philo 5 800 200 200 7 # No philo should die and simulation should stop after 7 meals
```
```sh
./philo 4 310 200 100 # Philo should die
```
