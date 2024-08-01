#include "p_inverse.h"

void conjugate_transpose(int rows, int cols, double complex A[rows][cols], double complex A_H[cols][rows]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            A_H[j][i] = conj(A[i][j]);
        }
    }
}

void multiply_matrices(int rows1, int cols1, int cols2, double complex A[rows1][cols1], double complex B[cols1][cols2], double complex C[rows1][cols2]) {
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            C[i][j] = 0.0 + 0.0 * I;
            for (int k = 0; k < cols1; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void pseudoinverse(int rows, int cols, double complex A[rows][cols], double complex A_pseudo[cols][rows]) {
    double complex A_H[cols][rows];
    conjugate_transpose(rows, cols, A, A_H);

    double complex A_H_A[cols][cols];
    multiply_matrices(cols, rows, cols, A_H, A, A_H_A);

    double complex A_H_A_inv[cols][cols];
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == j) {
                A_H_A_inv[i][j] = 1.0 / A_H_A[i][j];
            } else {
                A_H_A_inv[i][j] = 0.0 + 0.0 * I;
            }
        }
    }

    multiply_matrices(cols, cols, rows, A_H_A_inv, A_H, A_pseudo);
}

int p_inverse(){
    int rows = 30;
    int cols = 40;
    
    double complex A[rows][cols];
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double real = (double)(rand() % 100) / 10.0;
            double imag = (double)(rand() % 100) / 10.0;
            A[i][j] = real + imag * I;
        }
    }

    double complex A_pseudo[cols][rows];

    clock_t start_time = clock();
    pseudoinverse(rows, cols, A, A_pseudo);
    clock_t end_time = clock();

    double time_elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    return (int)(time_elapsed * 1000000); // microseconds
}