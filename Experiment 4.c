#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();
        printf("Thread %d says: Hello, I am Enrique!\n", id);
    }
    return 0;
}
