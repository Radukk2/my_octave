#include <stdio.h>
#ifndef MATLAB_FUNCTIONS_H
#define MATLAB_FUNCTIONS_H

int **alocare(int m, int n);

int verif(int nr);

void inmultire(int **mat, int **mat1, int **mat2, int i, int j, int nr);

void citire(int **matrix, int m, int n);

void determinarea_dimensiunilor(int *v1, int *v2, int i1, int indice);

void afisare_matrice(int *vect1, int *vect2, int i1, int ***vect3, int indice);

void mult(int *i1, int *i2, int ****vect3, int **vect1, int **vect2, int *ind);

int **get_M1(int **A, int **B, int dim);

int **get_M2(int **A, int **B, int dim);

int **get_M3(int **A, int **B, int dim);

int **get_M4(int **A, int **B, int dim);

int **get_M5(int **A, int **B, int dim);

int **get_M6(int **A, int **B, int dim);

int **get_M7(int **A, int **B, int dim);

int **get_strassen(int **A, int **B, int dim);

void strassen(int *i1, int *i2, int ****vect3,
			  int **vect1, int **vect2, int *ind);

void redimensionare(int ***vect1, int *v2, int *v3, int indice, int i1);

int s(int **matrix, int m, int n);

void sortare(int ****v_i, int *v_l, int *v_c, int indice);

void transpunere(int i1, int ***matrix,  int *v1, int *v2, int indice);

void power(int i1, int ***v1, int *v2, int *v3, int indice, int pow);

void eliberare(int ****vect_index, int **v1, int **v2, int *indice, int i1);

void eliberare_fortata(int ***vect_index, int *v1, int *v2, int indice);
#endif // MATLAB_FUNCTIONS_H
