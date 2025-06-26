#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to print a matrix
void print_matrix(double *matrix, int rows, int cols, const char *name) {
    printf("Matrix %s (%d x %d):\n", name, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%8.2f ", matrix[i * cols + j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int world_rank, world_size;
    double *matrix_a = NULL;
    double *matrix_b = NULL;
    double *matrix_c = NULL;
    double *local_a = NULL;
    double *local_c = NULL;

    // Define matrix dimensions
    // A: M x K, B: K x N, C: M x N
    int M = 6; // Rows of A and C
    int K = 4; // Columns of A and Rows of B
    int N = 5; // Columns of B and C

    if (argc == 4) {
        M = atoi(argv[1]);
        K = atoi(argv[2]);
        N = atoi(argv[3]);
    } else if (argc != 1 && argc != 4) {
        printf("Usage: %s [M K N]\n", argv[0]);
        return 1;
    }


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (M % world_size != 0) {
        if (world_rank == 0) {
            fprintf(stderr, "Error: Number of rows M (%d) must be divisible by the number of processes (%d).\n", M, world_size);
        }
        MPI_Finalize();
        return 1;
    }

    int rows_per_process = M / world_size;

    // Allocate memory for local_a and local_c for all processes
    local_a = (double *)malloc(rows_per_process * K * sizeof(double));
    // Matrix B (local_b) will be the same for all, so allocate it directly.
    // No, matrix_b is allocated by root and then broadcasted.
    // All processes need space to receive matrix_b.
    matrix_b = (double *)malloc(K * N * sizeof(double)); // All processes need a copy of B
    local_c = (double *)malloc(rows_per_process * N * sizeof(double));

    if (local_a == NULL || matrix_b == NULL || local_c == NULL) {
        fprintf(stderr, "Memory allocation failed on rank %d\n", world_rank);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (world_rank == 0) {
        // Master process initializes matrices A and B
        matrix_a = (double *)malloc(M * K * sizeof(double));
        // matrix_b is already allocated above for all processes.
        // Here, rank 0 will fill its copy.
        matrix_c = (double *)malloc(M * N * sizeof(double));

        if (matrix_a == NULL || matrix_c == NULL) {
            fprintf(stderr, "Memory allocation failed on master process\n");
            free(local_a); // Free previously allocated memory before aborting
            free(matrix_b);
            free(local_c);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        // Initialize matrices A and B with some values
        srand(time(NULL)); // Seed random number generator
        for (int i = 0; i < M * K; i++) {
            matrix_a[i] = (double)(rand() % 100) / 10.0; // Values between 0.0 and 9.9
        }
        for (int i = 0; i < K * N; i++) {
            matrix_b[i] = (double)(rand() % 100) / 10.0;
        }

        // print_matrix(matrix_a, M, K, "A");
        // print_matrix(matrix_b, K, N, "B");
    }

    // Scatter rows of matrix A from master (rank 0) to all processes
    // Each process receives rows_per_process * K elements
    MPI_Scatter(matrix_a, rows_per_process * K, MPI_DOUBLE,
                local_a, rows_per_process * K, MPI_DOUBLE,
                0, MPI_COMM_WORLD);

    // Broadcast matrix B from master (rank 0) to all processes
    // All processes receive K * N elements
    MPI_Bcast(matrix_b, K * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Perform local matrix multiplication: local_c = local_a * matrix_b
    for (int i = 0; i < rows_per_process; i++) {
        for (int j = 0; j < N; j++) {
            local_c[i * N + j] = 0.0;
            for (int l = 0; l < K; l++) {
                local_c[i * N + j] += local_a[i * K + l] * matrix_b[l * N + j];
            }
        }
    }

    // Gather results from all processes to matrix_c on master (rank 0)
    // Each process sends rows_per_process * N elements
    MPI_Gather(local_c, rows_per_process * N, MPI_DOUBLE,
               matrix_c, rows_per_process * N, MPI_DOUBLE,
               0, MPI_COMM_WORLD);

    // Master process prints the result matrix C
    if (world_rank == 0) {
        // print_matrix(matrix_c, M, N, "C (Result)");

        // Verification (optional, simple sequential multiplication)
        printf("Verification (M=%d, K=%d, N=%d, P=%d):\n", M, K, N, world_size);
        int errors = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                double expected_value = 0.0;
                for (int l = 0; l < K; l++) {
                    expected_value += matrix_a[i * K + l] * matrix_b[l * N + j];
                }
                if (abs(matrix_c[i * N + j] - expected_value) > 1e-6) { // Compare with tolerance
                    // printf("Error at C[%d][%d]: Expected %.2f, Got %.2f\n", i, j, expected_value, matrix_c[i * N + j]);
                    errors++;
                }
            }
        }
        if (errors == 0) {
            printf("Matrix multiplication successful. Result matches sequential computation.\n");
        } else {
            printf("Matrix multiplication INCORRECT. Found %d differing elements.\n", errors);
            // If errors, print matrices for debugging if small enough
            if (M <= 10 && K <= 10 && N <= 10) {
                 print_matrix(matrix_a, M, K, "A (Sent)");
                 print_matrix(matrix_b, K, N, "B (Sent)");
                 print_matrix(matrix_c, M, N, "C (MPI Result)");

                // Print expected C
                double* expected_c_matrix = (double*)malloc(M * N * sizeof(double));
                 for (int i = 0; i < M; i++) {
                    for (int j = 0; j < N; j++) {
                        expected_c_matrix[i*N+j] = 0;
                        for (int l = 0; l < K; l++) {
                           expected_c_matrix[i*N+j] += matrix_a[i * K + l] * matrix_b[l * N + j];
                        }
                    }
                }
                print_matrix(expected_c_matrix, M, N, "C (Expected Sequential)");
                free(expected_c_matrix);
            }
        }
    }

    // Free allocated memory
    if (world_rank == 0) {
        free(matrix_a);
        // matrix_b is freed by all processes
        free(matrix_c);
    }
    free(local_a);
    free(matrix_b); // All processes free their copy of B
    free(local_c);

    MPI_Finalize();
    return 0;
}
