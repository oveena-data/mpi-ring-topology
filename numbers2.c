// Name: Sandali Oveena Widyaratne
// Student ID: A1882491
// Description: numbers2.c reads each process's number from stdin.
// Process 0 is the master and collects out-of-order reports in rank order.

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    // Initialise the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the current process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Define the numbers for each process
    int numbers[5] = {5, 7, 9, 1, 13};
    // Get the number for the current process
    int my_number = numbers[world_rank];

    // Determine the rank of the right neighbour
    int right_neighbour = (world_rank + 1) % world_size;
    // Determine the rank of the left neighbour
    int left_neighbour = (world_rank - 1 + world_size) % world_size;

    // Send number to right neighbour
    MPI_Send(&my_number, 1, MPI_INT, right_neighbour, 0, MPI_COMM_WORLD);

    // Receive number from left neighbour
    int left_number;
    MPI_Recv(&left_number, 1, MPI_INT, left_neighbour, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Store if the number is out of order
    int out_of_order = 0;
    // Store the total number of out of order numbers
    int total_out_of_order = 0;

    if (world_rank == 0) {
        // Master process
        for (int i = 1; i < world_size; i++) {
            // Receive out_of_order from each process
            MPI_Recv(&out_of_order, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // Check if the number is out of order
            if (out_of_order) {
                // Print out of order number
                printf("Process %d has number %d out of order.\n", i, numbers[i]);
                // Increment total out of order numbers
                total_out_of_order++;
            }
        }
        // Print total number of out of order numbers
        printf("The number of processes holding an out-of-order number is %d.\n", total_out_of_order);

    } else {
        // Worker process
        // Compare the number with the number received from the left neighbour
        if (my_number < left_number) {
            out_of_order = 1;
        }
        // Send result to master process
        MPI_Send(&out_of_order, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // Finalise the MPI environment
    MPI_Finalize();

    return 0;
}