# Philosophers

This project was made to make us learn about threads, and how they interact with mutex.

The goal was to monitor a group of `P` philosophers(threads) that needs to eat every `X` ms, or else they die and the simulation ends.

The cycle goes like this: -Take a fork, take a second fork, eat `Y` ms, sleep `Z` ms, then think as long as no fork is available.

A philosopher cannot eat without two forks(mutex) and obviously a taken fork cannot be used by it's owner.

An optional variable could be added (`N`), which represent the number of time each philosopher had to eat before ending the simulation.

The program is launched this way: ``./philo P X Y Z (N)``

The result looks like this:

<img width="2560" alt="Screen Shot 2023-04-11 at 8 33 02 AM" src="https://user-images.githubusercontent.com/100093373/231163440-3de91d41-2edb-433c-8eda-431411676c07.png">
