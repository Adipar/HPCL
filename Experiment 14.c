#include <stdio.h>
#include <cuda_runtime.h>

#define N 512  // Matrix dimensions (N x N)

// CUDA kernel for matrix multiplication
__global__ void matrixMultiply(int *A, int *B, int *C, int n) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;  // Row index of C
    int col = blockIdx.x * blockDim.x + threadIdx.x;  // Column index of C

    if (row < n && col < n) {
        int value = 0;
        for (int i = 0; i < n; i++) {
            value += A[row * n + i] * B[i * n + col];
        }
        C[row * n + col] = value;
    }
}

int main() {
    int *A, *B, *C;        // Matrices A, B, and C
    int *d_A, *d_B, *d_C;   // Device matrices

    int size = N * N * sizeof(int);  // Size of each matrix

    // Allocate memory for matrices on host
    A = (int *)malloc(size);
    B = (int *)malloc(size);
    C = (int *)malloc(size);

    // Initialize the matrices A and B with sample values
    for (int i = 0; i < N * N; i++) {
        A[i] = i;
        B[i] = i * 2;
    }

    // Allocate memory for matrices on device
    cudaMalloc((void **)&d_A, size);
    cudaMalloc((void **)&d_B, size);
    cudaMalloc((void **)&d_C, size);

    // Copy matrices from host to device
    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    // Define block and grid size
    dim3 blockSize(16, 16);  // 16x16 threads per block
    dim3 gridSize((N + blockSize.x - 1) / blockSize.x, (N + blockSize.y - 1) / blockSize.y);

    // Launch the kernel
    matrixMultiply<<<gridSize, blockSize>>>(d_A, d_B, d_C, N);

    // Wait for GPU to finish before accessing on host
    cudaDeviceSynchronize();

    // Copy the result matrix from device to host
    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    // Print the result (only first 10 elements for brevity)
    printf("Matrix C (first 10 elements):\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", C[i]);
    }
    printf("\n");

    // Free device memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    // Free host memory
    free(A);
    free(B);
    free(C);

    return 0;
}
