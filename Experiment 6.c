#include <stdio.h>
#include <omp.h>

int main() {
    // Declare an integer variable
    int val = 1234;

    // Print the initial value of val
    printf("Initial value of val: %d\n", val);

    // Parallel region with private clause
    #pragma omp parallel num_threads(4) private(val)
    {
        // Get the thread ID
        int thread_id = omp_get_thread_num();

        // val is private, uninitialized, and must be explicitly set
        val = thread_id * 10; // Assign a unique value based on thread ID

        // Print the current value of val for this thread
        printf("Thread %d: val = %d\n", thread_id, val);

        // Modify the private variable
        val += 5;

        // Print the updated value of val for this thread
        printf("Thread %d: Updated val = %d\n", thread_id, val);
    }

    // Print the final value of val after the parallel region
    printf("Final value of val after parallel region: %d\n", val);

    return 0;
}
