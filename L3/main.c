#include <stdio.h>
#include <stdlib.h>

#define N 10

// Function to initialize and input a matrix
double** init_input_matrix() {
    // Dynamically allocate memory for an N x N matrix
    double** matrix = (double**) malloc(N * sizeof(double*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (double*) malloc(N * sizeof(double));
    }

    // Read values into the matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%lf", &matrix[i][j]);  // Corrected format specifier for double
        }
    }

    return matrix;
}

int main() {
    // Get the input matrix
    double** matrix = init_input_matrix();

    // Print the matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }

    // Free the dynamically allocated memory
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
