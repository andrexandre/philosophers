# Philosophers

This project is a simulation of the classic Dining Philosophers problem, a synchronization and resource sharing problem in computer science. The challenge is to design a solution where philosophers must eat and think without starving, using shared resources (forks) that must be held by only one philosopher at a time

## Description
In this project, each philosopher is a thread, and each fork is a mutex. The philosophers sit around a circular table with a large bowl of spaghetti in the middle. There are as many forks as philosophers on the table. The philosophers alternatively eat, think, or sleep:
- To eat, a philosopher needs to pick up two forks (one from their left and one from their right)
- When a philosopher has finished eating, they put their forks back on the table and start sleeping
- Once awake, a philosopher starts thinking
- The simulation stops when a philosopher dies of starvation or when the optional parameter `[meals_needed]` is reached

## Usage

1. Clone the repository
```sh
git clone https://github.com/andrexandre/philosophers.git ; cd philosophers/philo
```

2. Compile the program
```sh
make
```

3. Run the program
```sh
./philo 5 800 200 200
```

### Parameters
- `number_of_philo`: Number of philosophers and forks
- `time_to_die`: Time in milliseconds after which a philosopher dies if they haven't started eating
- `time_to_eat`: Time in milliseconds it takes for a philosopher to eat
- `time_to_sleep`: Time in milliseconds a philosopher spends sleeping
- `[meals_needed]`: (Optional) Number of times each philosopher must eat before the simulation stops

> [!NOTE]
> This project is part of the 42 School curriculum
