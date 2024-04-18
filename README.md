# philosophers

philosophers is an individual 42 school project which introduces us to threading and processes and how to work on the same memory space.

## Status

* Success
* Grade: 125/100

## Rules

* One or more philosophers are sitting at a round table with a large bowl of spaghetti in the center.
* They are doing one of three things: eating, thinking or sleeping. While eating, they are not thinking or sleeping, while sleeping, they are not eating or thinking and of course, while thinking, they are not eating or sleeping.
* There are some forks on the table. There are forks as many as there are philosophers.
* As spaghetti is difficult to serve and eat with a single fork, it is assumed that a philosopher must eat with two forks, one for each hand.
* Each time a philosopher has finished eating, he will drop his forks and start sleeping. When he is done sleeping, he will start thinking.
* Every philosopher needs to eat and the philosophers must never be starving.
* Philosophers don't speak with each other.
* Philosophers don't know when another philosopher is about to die.
* The simulation stops when a philosopher dies.

Each program should have the same arguments:
* **number_of_philosophers**: is the number of philosophers and also the number of forks.
* **time_to_die** (in milliseconds): if a philosophers doesn't start eating '**time_to_die**' milliseconds after starting his last meal or the beginning of the simulation, he dies.
* **time_to_eat** (in milliseconds): is the time it takes for a philosopher to eat. During that time, he will need to keep the two forks.
* **time_to_sleep** (in milliseconds): is the time it takes for a philosopher to sleep.
* **number_of_times_each_philosopher_must_eat** (optional): if all philosophers eat at least '**number_of_times_each_philosopher_must_eat**' the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.

Each philosopher should be given a number from **1** to '**number_of _philosophers**'. Philosopher number **1** is next to philosopher number '**number_of _philosophers**'.
Any other philosopher with the number **N** is seated between philosopher **N - 1** and philosopher **N + 1**.

Any change of status of a philosopher must be written as follows (with ```X``` replaced with the philosopher):
* ```timestamp_in_ms X has taken a fork```
* ```timestamp_in_ms X is eating```
* ```timestamp_in_ms X is sleeping```
* ```timestamp_in_ms X is thinking```
* ```timestamp_in_ms X died```

The status printed should not be scrambled or intertwined with another philosopher's status. You can't have more than 10 ms between the death of a philosopher and when it will print its death.

### Mandatory

In this version, the specific rules are:
* One fork between each philosopher, therefore if they are multiple philosophers, there will be a fork at the right and left of each philosopher.
* To avoid philosophers duplicating forks, we should protect the forks state with a mutex for each of them.
* Each philosopher should be a thread.

### Bonus

In this version, the specific rules are:
* All the forks are in the middle of the table.
* They have no states in memory but the number of available forks is represented by a semaphore.
* Each philosopher should be a process and the main process should not be a philosopher.

## Project content

This project contains two folders. One for the mandatory part and the other for the bonus part.

## Usage

For each program, use ```make``` command to compile and run with:
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
or:
```
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
Example:
```
./philo 4 300 100 100 9
```
or:
```
./philo_bonus 4 300 100 100 9
```
***
Made by Thibaut Charpentier: <thibaut.charpentier42@gmail.com>
