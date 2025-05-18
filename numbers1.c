// Name: Sandali Oveena Widyaratne
// Student ID: A1882491
// Description: This program demonstrates the use of MPI (Message Passing Interface) to send and receive messages between processes in a ring topology using modular aarithmetic.
// Each process communicates only with its immediate neighbours (left and right) in the ring, using point-to-point communication.
// The goal is to identify whether a process holds a number that is out of order, meaning it is less than the number received from its left neighbour.


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    // Step 1
    // Initialize MPI - this will set up the MPI environment and must be called before any other MPI functions
    MPI_Init(&argc, &argv);

    // Step 2
    // Get the total number of processes involved in the computation
    // This is important for determining the size of the communicator
    // and for setting up the ring topology
    // This value should be 5 for this specific program.
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Step 3
    // Get the unique rank of the current process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Step 4
    // Define numbers for each process
    // Each process accesses the value at its index (rank) in the array
    int numbers[5] = {5, 7, 9, 1, 13};

    // Step 5
    // Retrieve the number assigned to this specific process
    int number = numbers[world_rank];

    // Step 6
    // Define neighbours in the ring topology:
    // In a ring, each process has 2 neighbours-
    // Left neighbour (rank - 1 + world_size) % world_size
    // Right neighbour (rank + 1) % world_size
    //
    // This logic makes sure that:
    // Process 0's left neighbour is Process 4
    // Process 4's right neighbour is Process 0
    int left_neighbour = (world_rank - 1 + world_size) % world_size;
    int right_neighbour = (world_rank + 1) % world_size;

    // Step 7
    // Send the number to the right neighbour
    // This is a blocking send operation, meaning the process will wait until the message is sent
    // before continuing. The message consists of the number, its size (1 integer), and the destination rank
    // The tag (0 in this case) is used to identify the message type, and the communicator (MPI_COMM_WORLD)
    // specifies the group of processes involved in the communication
    MPI_Send(&number, 1, MPI_INT, right_neighbour, 0, MPI_COMM_WORLD);

    // Step 8
    // Receive the number from the left neighbour
    // This value will be used for comparison to check if the numbers are in order or out-of-order
    int left_number;
    MPI_Recv(&left_number, 1, MPI_INT, left_neighbour, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Step 9
    // Check if this process has a number out of order
    // Process 0 is skipped from the comparision (no true left neighbour)
    // For other processes, if their number is less than the number received from the left neighbour,
    // it indicates that the number is out of order
    int my_number = numbers[world_rank];
    if(world_rank != 0 && my_number < left_number) {
        printf("Process %d has at least one number out of order. \n", world_rank);
    }

    // Step 10
    // Print a message indicating that the process has finished its work
    printf("Process %d has finished.\n", world_rank);

    // Step 11
    // Finalize MPI - this will clean up the MPI environment and should be called at the end of the program
    MPI_Finalize();

    // Step 12
    // Return 0 to indicate successful completion of the program
    return 0;
}