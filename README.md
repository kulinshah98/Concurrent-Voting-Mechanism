## Project Description

A concurrent process of voting where the threads representing evms, voters and booths run concurrently using conditional variables and mutex locks.

## Compile and Run

- Compile code using 'gcc polling.c -lpthread' command.
- Run code using './a.out'
- Input format:
    - N (Number of Booth) 
    - Next N lines:- (Number of voters) (Number of EVM) (max capacity of each EVM )

## Implementation Details

- Creating thread for each EVM and each voter.
- Voter thread will call voter function which will wait until he will allocate a EVM to vote.
- EVM thread will call EVM function. EVM function will generate a random number between 1 to max. capacity of that booth and allocate that many voter to that EVM. Now EVM thread will give signal to voter thread that voter is a given that EVM to vote then after Voting is done , Voter thread will terminate .After all voter of that booth is done then each EVM thread will terminate.
