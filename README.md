# CP386-Final-Assignment
The final assignment of the CP386 (Operating Systems) course

## Motivation
the honest answer: needs to be completed for marks :)

## Installation
### PRE-REQ
- Linux system
- GCC compiler

### Steps
1. clone the repository

2. 
- Option 1 - Compile and run the program manually
Compile the .c file manually with the following line in the command line by navigating to the path which the files are located.

Run the follow command 
`gcc -o [ANY NAME] [.c FILE NAME] -lpthread -lrt`
Then, 
`./[ANY NAME] X X X X`

**note** - [ANY NAME] should be the same from both steps, and Xs get replaced with integers

- Option 2 - use the Make file
## Screenshots

## Individual contribution
*(author, co-author)*

`int readFileCustomers(char *fileName);` - Jagveer

`void readFileSequences(char *fileName, int max[n_rows][n_col]);` - Jagveer, Robert

`bool safety(int *available, int *allocated, int *need);` - Robert, Jagveer

`int sum_arr(int arr[], int n);` - Robert, Jagveer

`void get_n_col(char *filename);` - Robert, Jagveer

`int bankersalgo();` - Jagveer

`void run_cmd();` - Jagveer, Robert

`int request_resource(int args[]);` - Robert, Jagveer

`int release_resource(int args[]);` - Robert, Jagveer

`void status(int *available, int *max, int *allocation, int *need);` - Robert, Jagveer

`Blood, sweat, and tears` - Robert and Jagveer equally.


## Features
### Commands
- Rquest Resource | RQ

Assigns resources to a specific customer from the available resources

```
Enter Command: RQ 1 2 3 1 1
```

- Release Resource | RL

Releases resource that are in use by a customer.

```
Enter Command: RL 1 1 1 1 1
```

- Run | run

Runs all the threads in it's safe sequence

```
Enter Command: run
```

- Status | status

Displays the current status of all the matricies

```
Enter Command: status
```

- Exit | exit

Terminates the program

```
Enter Command: exit
```
## Tests
Testing manually with print statements

## Code Example
## Authors
- [Robert Mazza](https://github.com/Robert336)
- [Jagveer Sangha](https://github.com/Jagveer-Sangha)
## Credits
## License
MIT
