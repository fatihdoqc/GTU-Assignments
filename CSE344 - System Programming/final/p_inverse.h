#ifndef P_INVERSE_H
#define P_INVERSE_H

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <time.h>


void conjugate_transpose(int rows, int cols, double complex A[rows][cols], double complex A_H[cols][rows]) ;
void multiply_matrices(int rows1, int cols1, int cols2, double complex A[rows1][cols1], double complex B[cols1][cols2], double complex C[rows1][cols2]) ;
void pseudoinverse(int rows, int cols, double complex A[rows][cols], double complex A_pseudo[cols][rows]) ;
int p_inverse();


#endif

