# philosophers

Two implementations of the Dining philosophers problem:
- Thread-safe implementation using mutexes
- Process-based implementation using semaphores

## Introduction

The Dining Philosophers problem is a classic synchronization problem in computer science. This project provides an implementation of the problem using multithreading and multiprocessing to simulate the behavior of philosophers dining and thinking.

## Features

- Simulates the Dining Philosophers problem.
- Configurable number of philosophers and timing parameters.

## Building

To install and run the project, follow these steps:

1. Clone the repository:
	```sh
	git clone git@github.com:42Core-vvoronts/philosophers.git
	```
2. Navigate to the project directory:
	```sh
	cd philosophers/thread_mutex
	```
	or
	```sh
	cd philosophers/process_semaphores
	```
3. Compile the project:
	```sh
	make
	```

## Usage

To run the program, use the following command:
```sh
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

Example:
```sh
./philo 5 800 200 200 7
```
