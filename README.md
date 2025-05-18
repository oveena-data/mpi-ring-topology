# MPI Project 

In a ring, each process has:

- A left neighbour (rank - 1 modulo total number of processes)
- A right neighbour (rank + 1 modulo total number of processes)

When emulating this topology using MPI, point-to-point communication must be used between immediate neighbours only.

Each program comprises a total of five processes. Each process contains a number. The objective is to find numbers out of order, and print information about them. The number in a process is said to be out of order if it is less than the number in its left neighbour. The ordering starts at process 0 (process 0 has no left neighbour).

### For example: 
- If processes 0 through to 4 contain, respectively, the numbers 5, 7, 9, 1 and 13, then the number 1 in rank 3 is out of order. All the others are in order.

### Expected Output:

- If a process has a number that is out of order, it should print: “Process <rank> has at least one number out of order.”
- It then prints an indication that it has terminated: “Process <rank> has now finished.”
