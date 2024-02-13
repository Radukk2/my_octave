
//#Copyright Constantinescu Radu 323CA 2023-2024
// Updated version of last years's homework
#include <stdio.h>
#include <stdlib.h>
#include "matlab_functions.h"

int **alocare(int m, int n)
{
	//functia de alocare
	//intai se aloca vectorul de linii
	int **a = malloc(m * sizeof(int *));
	if (!a)
		return NULL;
	//apoi aloc coloanele pe fiecare linie
	for (int i = 0; i < m; i++) {
		a[i] = malloc(n * sizeof(int));
		if (!a[i])
		    return NULL;
	}
	return a;
}

int verif(int nr)
{
	if (nr < 0)
		return nr + 10007;
	else
		return nr;
}

void inmultire(int **mat, int **mat1, int **mat2, int i, int j, int nr)
{
	//functie care determina elementul de pe pozitia i si j la inmultirea
	//a doua matrice
	for (int k = 0; k < nr; k++) {
		mat[i][j] += mat1[k][j] * mat2[i][k];
		mat[i][j] = mat[i][j] % 10007;
		if (mat[i][j] < 0)
			mat[i][j] += 10007;
	}
}

void citire(int **matrix, int m, int n)
{
	//functia de citire
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			scanf("%d", &matrix[i][j]);
	}
}

void determinarea_dimensiunilor(int *v1, int *v2, int i1, int indice)
{
	if (i1 > indice - 1 || i1 < 0)//verificare ca aceasta matrice exista
		printf("No matrix with the given index\n");
	else
		printf("%d %d\n", v1[i1], v2[i1]);//printam dimensiunile
}

void afisare_matrice(int *vect1, int *vect2, int i1, int ***vect3, int indice)
{
	if (i1 > indice - 1 || i1 < 0) {
		printf("No matrix with the given index\n");//verificare
	} else {//matricea se afiseaza ca clasic
		for (int i = 0; i < vect1[i1]; i++) {
			for (int j = 0; j < vect2[i1]; j++)
				printf("%d ", vect3[i1][i][j]);
			printf("\n");
		}
	}
}

void mult(int *i1, int *i2, int ****vect3, int **vect1, int **vect2, int *ind)
{
	if (((*i1) > (*ind) - 1 || (*i1) < 0) ||
		((*i2) > (*ind) - 1 || (*i2) < 0)) {//verific existenta matricelor
		printf("No matrix with the given index\n");
	} else {
		if ((*vect2)[*i1] == (*vect1)[*i2]) {//verificarea posibilitatii
		//executiei functiei create
			int **matrix = calloc((*vect1)[*i1], sizeof(int *));//alocare
			if (!matrix)
				exit(0);//programarea defensiva
			for (int i = 0; i < (*vect1)[*i1]; i++) {
				matrix[i] = calloc((*vect2)[*i2], sizeof(int));
				if (!matrix[i])
					exit(0);
			}
			for (int i = 0; i < (*vect1)[*i1]; i++)
				for (int j = 0; j < (*vect2)[*i2]; j++) {
					for (int k = 0; k < (*vect1)[*i2]; k++) {
						int x = (*vect3)[*i1][i][k] * (*vect3)[*i2][k][j];
						matrix[i][j] += x;//determinarea elem matrricei finale
						matrix[i][j] = matrix[i][j] % 10007;
						matrix[i][j] = verif(matrix[i][j]);
					}
				} //inmultirea conforem regulilor problemei
			(*vect3) = realloc((*vect3), (*ind + 1) * sizeof(int **));
			//adaugam matricea la finalul sirului
			(*vect3)[*ind] = alocare((*vect1)[*i1], (*vect2)[*i2]);
			(*vect1) = realloc((*vect1), (*ind + 1) * sizeof(int));
			//procedam similar si pentru dimensiunile acesteia
			(*vect2) = realloc((*vect2), (*ind + 1) * sizeof(int));
			(*vect1)[*ind] = (*vect1)[*i1];
			(*vect2)[*ind] = (*vect2)[*i2];
			for (int i = 0; i < (*vect1)[*i1]; i++)
				for (int j = 0; j < (*vect2)[*i2]; j++)
					(*vect3)[*ind][i][j] = matrix[i][j];
			//eliberam elementul auxiliar din functie
			for (int i = 0; i < (*vect1)[*i1]; i++)
				free(matrix[i]);
			free(matrix);
			*ind  += 1;
		} else {
			printf("Cannot perform matrix multiplication\n");
			//in cazul in care nu pot inmultii matricele
		}
	}
}

//aflua matricea M1
int **get_M1(int **A, int **B, int dim)
{
	int **m1  = calloc(dim / 2, sizeof(int *));//alocare
			if (!m1)
				exit(0);//programarea defensiva
			for (int i = 0; i < dim / 2; i++) {
				m1[i] = calloc(dim / 2, sizeof(int));
				if (!m1[i])
					exit(0);
			}
	int **a_corners  = calloc(dim / 2, sizeof(int *));//alocare
			if (!a_corners)
				exit(0);//programarea defensiva
			for (int i = 0; i < dim / 2; i++) {
				a_corners[i] = calloc(dim / 2, sizeof(int));
				if (!a_corners[i])
					exit(0);
			}
	int **b_corners  = calloc(dim / 2, sizeof(int *));//alocare
		if (!b_corners)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			b_corners[i] = calloc(dim / 2, sizeof(int));
			if (!b_corners[i])
				exit(0);
		}
	//Aflu A1 + A4 si B1 + B4
	for (int i = 0; i < dim / 2; i++)
		for (int j = 0; j < dim / 2; j++) {
			a_corners[i][j] = A[i][j] + A[i + dim / 2][j + dim / 2];
			b_corners[i][j] = B[i][j] + B[i + dim / 2][j + dim / 2];
		}
	for (int i = 0; i < dim / 2; i++)
		for (int j = 0; j < dim / 2; j++)
			for (int k = 0; k < dim / 2; k++)
				m1[i][j] += a_corners[i][k] * b_corners[k][j];
	//Eliberez memoria
	for (int i = 0; i < dim / 2; i++) {
		free(a_corners[i]);
		free(b_corners[i]);
	}
	free(a_corners);
	free(b_corners);
	return m1;
}

//aflua matricea M2
int **get_M2(int **A, int **B, int dim)
{
	int **m2  = calloc(dim / 2, sizeof(int *));//alocare
			if (!m2)
				exit(0);//programarea defensiva
			for (int i = 0; i < dim / 2; i++) {
				m2[i] = calloc(dim / 2, sizeof(int));
				if (!m2[i])
					exit(0);
			}
	int **a_down  = calloc(dim / 2, sizeof(int *));//alocare
			if (!a_down)
				exit(0);//programarea defensiva
			for (int i = 0; i < dim / 2; i++) {
				a_down[i] = calloc(dim / 2, sizeof(int));
				if (!a_down[i])
					exit(0);
			}
	int **b_top_left  = calloc(dim / 2, sizeof(int *));//alocare
		if (!b_top_left)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			b_top_left[i] = calloc(dim / 2, sizeof(int));
			if (!b_top_left[i])
				exit(0);
		}
	// aflu A3 + A4 si B1
	for (int i = 0; i < dim / 2; i++)
		for (int j = 0; j < dim / 2; j++) {
			a_down[i][j] = A[i + dim / 2][j] + A[i + dim / 2][j + dim / 2];
			b_top_left[i][j] = B[i][j];
		}
	for (int i = 0; i < dim / 2; i++)
		for (int j = 0; j < dim / 2; j++)
			for (int k = 0; k < dim / 2; k++)
				m2[i][j] += a_down[i][k] * b_top_left[k][j];
	//Eliberez memoria
	for (int i = 0; i < dim / 2; i++) {
		free(a_down[i]);
		free(b_top_left[i]);
	}
	free(a_down);
	free(b_top_left);
	return m2;
}

//Calculez matricea M3
int **get_M3(int **A, int **B, int dim)
{
	int **m3  = calloc(dim / 2, sizeof(int *));//alocare
		if (!m3)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			m3[i] = calloc(dim / 2, sizeof(int));
			if (!m3[i])
				exit(0);
		}
	int **a_top_left  = calloc(dim / 2, sizeof(int *));//alocare
		if (!a_top_left)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			a_top_left[i] = calloc(dim / 2, sizeof(int));
			if (!a_top_left[i])
				exit(0);
		}
	int **b_left  = calloc(dim / 2, sizeof(int *));//alocare
		if (!b_left)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			b_left[i] = calloc(dim / 2, sizeof(int));
			if (!b_left[i])
				exit(0);
		}
	// aflu A1 si B2 - B4
	for (int i = 0; i < dim / 2; i++)
		for (int j = 0; j < dim / 2; j++) {
			a_top_left[i][j] = A[i][j];
			b_left[i][j] = B[i][j + dim / 2] - B[i + dim / 2][j + dim / 2];
		}
	for (int i = 0; i < dim / 2; i++)
		for (int j = 0; j < dim / 2; j++)
			for (int k = 0; k < dim / 2; k++)
				m3[i][j] += a_top_left[i][k] * b_left[k][j];
	//Eliberez memoria
	for (int i = 0; i < dim / 2; i++) {
		free(a_top_left[i]);
		free(b_left[i]);
	}
	free(a_top_left);
	free(b_left);
	return m3;
}

//Calculez matricea ajutatoare M4
int **get_M4(int **A, int **B, int dim)
{
	int **m4  = calloc(dim / 2, sizeof(int *));//alocare
		if (!m4)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			m4[i] = calloc(dim / 2, sizeof(int));
			if (!m4[i])
				exit(0);
		}
	int **a_bottom_left  = calloc(dim / 2, sizeof(int *));//alocare
		if (!a_bottom_left)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			a_bottom_left[i] = calloc(dim / 2, sizeof(int));
			if (!a_bottom_left[i])
				exit(0);
		}
	int **b_left  = calloc(dim / 2, sizeof(int *));//alocare
		if (!b_left)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			b_left[i] = calloc(dim / 2, sizeof(int));
			if (!b_left[i])
				exit(0);
		}
	//Aflu A4 si B3 - B1
	for (int i = 0; i < dim / 2; i++)
		for (int j = 0; j < dim / 2; j++) {
			a_bottom_left[i][j] = A[i + dim / 2][j + dim / 2];
			b_left[i][j] = B[i + dim / 2][j] - B[i][j];
		}
	for (int i = 0; i < dim / 2; i++)
		for (int j = 0; j < dim / 2; j++)
			for (int k = 0; k < dim / 2; k++)
				m4[i][j] += a_bottom_left[i][k] * b_left[k][j];
	//Eliberez memoria
	for (int i = 0; i < dim / 2; i++) {
		free(a_bottom_left[i]);
		free(b_left[i]);
	}
	free(a_bottom_left);
	free(b_left);
	return m4;
}

//Calculez matricea ajutatoare M5
int **get_M5(int **A, int **B, int dim)
{
	int **m5 = calloc(dim / 2, sizeof(int *));//alocare
		if (!m5)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			m5[i] = calloc(dim / 2, sizeof(int));
			if (!m5[i])
				exit(0);
		}
	int **a_top  = calloc(dim / 2, sizeof(int *));//alocare
		if (!a_top)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			a_top[i] = calloc(dim / 2, sizeof(int));
			if (!a_top[i])
				exit(0);
		}
	int **b_bottom_right  = calloc(dim / 2, sizeof(int *));//alocare
		if (!b_bottom_right)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			b_bottom_right[i] = calloc(dim / 2, sizeof(int));
			if (!b_bottom_right[i])
				exit(0);
		}
	//Aflu A1 + A2 si B4
	for (int i = 0; i < dim / 2; i++)
		for (int j = 0; j < dim / 2; j++) {
			a_top[i][j] = A[i][j] + A[i][j + dim / 2];
			b_bottom_right[i][j] = B[i + dim / 2][j + dim / 2];
		}
	for (int i = 0; i < dim / 2; i++)
		for (int j = 0; j < dim / 2; j++)
			for (int k = 0; k < dim / 2; k++)
				m5[i][j] += a_top[i][k] * b_bottom_right[k][j];
	//Eliberez memoria
	for (int i = 0; i < dim / 2; i++) {
		free(a_top[i]);
		free(b_bottom_right[i]);
	}
	free(a_top);
	free(b_bottom_right);
	return m5;
}

//Calculez matricea ajutatoare M6
int **get_M6(int **A, int **B, int dim)
{
	int **m6 = calloc(dim / 2, sizeof(int *));//alocare
		if (!m6)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			m6[i] = calloc(dim / 2, sizeof(int));
			if (!m6[i])
				exit(0);
		}
	int **a_left  = calloc(dim / 2, sizeof(int *));//alocare
		if (!a_left)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			a_left[i] = calloc(dim / 2, sizeof(int));
			if (!a_left[i])
				exit(0);
		}
	int **b_top  = calloc(dim / 2, sizeof(int *));//alocare
		if (!b_top)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			b_top[i] = calloc(dim / 2, sizeof(int));
			if (!b_top[i])
				exit(0);
		}
	//Aflu A3 - A1 si B1 + B2
	for (int i = 0; i < dim / 2; i++)
		for (int j = 0; j < dim / 2; j++) {
			a_left[i][j] = A[i + dim / 2][j] - A[i][j];
			b_top[i][j] = B[i][j] + B[i][j + dim / 2];
		}
	for (int i = 0; i < dim / 2; i++)
		for (int j = 0; j < dim / 2; j++)
			for (int k = 0; k < dim / 2; k++)
				m6[i][j] += a_left[i][k] * b_top[k][j];
	//Eliberez memoria
	for (int i = 0; i < dim / 2; i++) {
		free(a_left[i]);
		free(b_top[i]);
	}
	free(a_left);
	free(b_top);
	return m6;
}

//Calculez matricea ajutatoare M7
int **get_M7(int **A, int **B, int dim)
{
	int **m7 = calloc(dim / 2, sizeof(int *));//alocare
		if (!m7)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			m7[i] = calloc(dim / 2, sizeof(int));
			if (!m7[i])
				exit(0);
		}
	int **a_right  = calloc(dim / 2, sizeof(int *));//alocare
		if (!a_right)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			a_right[i] = calloc(dim / 2, sizeof(int));
			if (!a_right[i])
				exit(0);
		}
	int **b_bottom  = calloc(dim / 2, sizeof(int *));//alocare
		if (!b_bottom)
			exit(0);//programarea defensiva
		for (int i = 0; i < dim / 2; i++) {
			b_bottom[i] = calloc(dim / 2, sizeof(int));
			if (!b_bottom[i])
				exit(0);
		}
	//Aflu A2 - A4 si B3 + B4
	for (int i = 0; i < dim / 2; i++)
		for (int j = 0; j < dim / 2; j++) {
			a_right[i][j] = A[i][j + dim / 2] - A[i + dim / 2][j + dim / 2];
			b_bottom[i][j] = B[i + dim / 2][j] + B[i + dim / 2][j + dim / 2];
		}
	for (int i = 0; i < dim / 2; i++)
		for (int j = 0; j < dim / 2; j++)
			for (int k = 0; k < dim / 2; k++)
				m7[i][j] += a_right[i][k] * b_bottom[k][j];
	//Eliberez memoria
	for (int i = 0; i < dim / 2; i++) {
		free(a_right[i]);
		free(b_bottom[i]);
	}
	free(a_right);
	free(b_bottom);
	return m7;
}

//Calculez cu ajutorul algoritmului
int **get_strassen(int **A, int **B, int dim)
{
	int **matrix = calloc(dim, sizeof(int *));//alocare
			if (!matrix)
				exit(0);//programarea defensiva
			for (int i = 0; i < dim; i++) {
				matrix[i] = calloc(dim, sizeof(int));
				if (!matrix[i])
					exit(0);
			}
	//Calculez matricele ajutatoare
	int **m1 = get_M1(A, B, dim);
	int **m2 = get_M2(A, B, dim);
	int **m3 = get_M3(A, B, dim);
	int **m4 = get_M4(A, B, dim);
	int **m5 = get_M5(A, B, dim);
	int **m6 = get_M6(A, B, dim);
	int **m7 = get_M7(A, B, dim);
	//Compun matricea
	for (int i = 0; i < dim / 2; i++)
		for (int j = 0; j < dim / 2; j++) {
			matrix[i][j] = m1[i][j] + m4[i][j] - m5[i][j] + m7[i][j];
			matrix[i][j] %= 10007;
			matrix[i][j] = verif(matrix[i][j]);
			matrix[i][j + dim / 2] = m3[i][j] + m5[i][j];
			matrix[i][j + dim / 2] %= 10007;
			matrix[i][j + dim / 2] = verif(matrix[i][j + dim / 2]);
			matrix[i + dim / 2][j] = m2[i][j] + m4[i][j];
			matrix[i + dim / 2][j] %= 10007;
			matrix[i + dim / 2][j] = verif(matrix[i + dim / 2][j]);
			matrix[i + dim / 2][j + dim / 2] = m1[i][j] - m2[i][j] + m3[i][j];
			matrix[i + dim / 2][j + dim / 2] += m6[i][j];
			matrix[i + dim / 2][j + dim / 2] %= 10007;
			matrix[i + dim / 2][j + dim / 2] =
			verif(matrix[i + dim / 2][j + dim / 2]);
		}
	//Eliberez memoria
	for (int i = 0; i < dim / 2; i++) {
		free(m1[i]);
		free(m2[i]);
		free(m3[i]);
		free(m4[i]);
		free(m5[i]);
		free(m6[i]);
		free(m7[i]);
	}
	free(m1);
	free(m2);
	free(m3);
	free(m4);
	free(m5);
	free(m6);
	free(m7);
	return matrix;
}

void strassen(int *i1, int *i2, int ****vect3,
			  int **vect1, int **vect2, int *ind)
{
	if (((*i1) > (*ind) - 1 || (*i1) < 0) ||
		((*i2) > (*ind) - 1 || (*i2) < 0)) {//verific existenta matricelor
		printf("No matrix with the given index\n");
	} else {
		if ((*vect2)[*i1] == (*vect1)[*i2]) {
			int **mat_A = calloc((*vect1)[*i1], sizeof(int *));//alocare
			if (!mat_A)
				exit(0);//programarea defensiva
			for (int i = 0; i < (*vect1)[*i1]; i++) {
				mat_A[i] = calloc((*vect1)[*i1], sizeof(int));
				if (!mat_A[i])
					exit(0);
			}
			for (int i = 0; i < (*vect1)[*i1]; i++)
				for (int j = 0; j < (*vect2)[*i1]; j++) {
					int x = (*vect3)[*i1][i][j];
					mat_A[i][j] += x;
				}
			int **mat_B = calloc((*vect1)[*i1], sizeof(int *));//alocare
			if (!mat_B)
				exit(0);//programarea defensiva
			for (int i = 0; i < (*vect1)[*i2]; i++) {
				mat_B[i] = calloc((*vect1)[*i2], sizeof(int));
				if (!mat_B[i])
					exit(0);
			}
			for (int i = 0; i < (*vect1)[*i2]; i++)
				for (int j = 0; j < (*vect2)[*i2]; j++) {
					int x = (*vect3)[*i2][i][j];
					mat_B[i][j] += x;
				}
			int **matrix = get_strassen(mat_A, mat_B, (*vect1)[*i1]);
			for (int i = 0; i < (*vect1)[*i1]; i++)
				free(mat_A[i]);
			free(mat_A);
			for (int i = 0; i < (*vect1)[*i2]; i++)
				free(mat_B[i]);
			free(mat_B);
			 //inmultirea conforem regulilor problemei
			(*vect3) = realloc((*vect3), (*ind + 1) * sizeof(int **));
			//adaugam matricea la finalul sirului
			(*vect3)[*ind] = alocare((*vect1)[*i1], (*vect2)[*i2]);
			(*vect1) = realloc((*vect1), (*ind + 1) * sizeof(int));
			//procedam similar si pentru dimensiunile acesteia
			(*vect2) = realloc((*vect2), (*ind + 1) * sizeof(int));
			(*vect1)[*ind] = (*vect1)[*i1];
			(*vect2)[*ind] = (*vect2)[*i2];
			for (int i = 0; i < (*vect1)[*i1]; i++)
				for (int j = 0; j < (*vect2)[*i2]; j++)
					(*vect3)[*ind][i][j] = matrix[i][j];
			//eliberam elementul auxiliar din functie
			for (int i = 0; i < (*vect1)[*i1]; i++)
				free(matrix[i]);
			free(matrix);
			*ind  += 1;
		} else {
			printf("Cannot perform matrix multiplication\n");
			//in cazul in care nu pot inmultii matricele
		}
	}
}

void redimensionare(int ***vect1, int *v2, int *v3, int indice, int i1)
{
	if (i1 > indice - 1 || i1 < 0) {
		int a, b, x;
		scanf("%d", &a);
		for (int i = 0; i < a; i++)
			scanf("%d", &x);
		scanf("%d", &b);
		for (int i = 0; i < b; i++)
			scanf("%d", &x);
		printf("No matrix with the given index\n");//verificare
	} else {
		int nr_lin;
		int *l;
		scanf("%d", &nr_lin);
		l = calloc(nr_lin, sizeof(int));
		if (!l)
			exit(0);
	    for (int i = 0; i < nr_lin; i++)
		    scanf("%d", &l[i]);
	    int nr_col, *c;
	    scanf("%d", &nr_col);
		c = calloc(nr_col, sizeof(int));
		if (!c)
			exit(0);
		for (int i = 0; i < nr_col; i++)
			scanf("%d", &c[i]);
		//am citit numarul de linii ,liniile, numarul de coloane
		//si coloanele pe care vreau sa le redimensionez
		//lucrez in place, deci pot opera direct pe valori
		int copie1 = v2[i1];
		v2[i1] = nr_lin;
		v3[i1] = nr_col;
	    int **matrix = alocare(nr_lin, nr_col);
	    for (int i = 0; i < nr_lin; i++)
		    for (int j = 0; j < nr_col; j++)
			    matrix[i][j] = vect1[i1][l[i]][c[j]];
		for (int i = 0; i < copie1; i++)
		//creez matricea rezultata
			free(vect1[i1][i]);
		free(vect1[i1]);
		//elimin matricea veche si o inlocuiesc cu cea noua
		vect1[i1] = alocare(nr_lin, nr_col);
		for (int i = 0; i < nr_lin; i++)
			for (int j = 0; j < nr_col; j++)
				vect1[i1][i][j] = matrix[i][j];
		free(l);
		free(c);
		for (int i = 0; i < nr_lin; i++)
			free(matrix[i]);
		free(matrix);
	}
}

int s(int **matrix, int m, int n)
{
	int s = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			s += matrix[i][j];
	s = s % 10007;
	if (s < 0)
		s += 10007;
	return s;
}

void sortare(int ****v_i, int *v_l, int *v_c, int indice)
{
	for (int i = 0; i < indice - 1; i++)
		for (int j = i + 1; j < indice; j++) {
			if (s((*v_i)[i], v_l[i], v_c[i]) > s((*v_i)[j], v_l[j], v_c[j])) {
				int **aux = (*v_i)[i];
				(*v_i)[i] = (*v_i)[j];
				(*v_i)[j] = aux;
				int aux1 = v_l[i];
				v_l[i] = v_l[j];
				v_l[j] = aux1;
				int aux2 = v_c[i];
				v_c[i] = v_c[j];
				v_c[j] = aux2;
			}
		} //sorteze adresele matricelor in functie e cea la care se gaseste
		//suma cea mai mare
}

void transpunere(int i1, int ***matrix,  int *v1, int *v2, int indice)
{
	if (i1 > indice - 1 || i1 < 0) {
		printf("No matrix with the given index\n");
	} else {
		int copie1 = v1[i1];
		int copie2 = v2[i1];
		int **mat_aux;//operatia este similara cu redimensionarea
		//lucrez tot in place cu o matrice auxiliara pe care o voi
		//pune in locul celei vechi
		mat_aux = alocare(v2[i1], v1[i1]);
		for (int i = 0; i < v1[i1]; i++)
			for (int j = 0; j < v2[i1]; j++)
				mat_aux[j][i] = matrix[i1][i][j];
		for (int i = 0; i < copie1; i++)
			free(matrix[i1][i]);
		free(matrix[i1]);
		v1[i1] = copie2;
		v2[i1] = copie1;
		matrix[i1] = alocare(v1[i1], v2[i1]);
		for (int i = 0; i < v1[i1]; i++)
			for (int j = 0; j < v2[i1]; j++)
				matrix[i1][i][j] = mat_aux[i][j];
		for (int i = 0; i < v1[i1]; i++)
			free(mat_aux[i]);
		free(mat_aux);
	}
}

void power(int i1, int ***v1, int *v2, int *v3, int indice, int pow)
{
	if (i1 > indice || i1 < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	if (v2[i1] != v3[i1]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	if (pow < 0) {
		printf("Power should be positive\n");
		return;
	} //cazurile in care operatia nu se poate efectua
		int **p = alocare(v2[i1], v3[i1]);
		int **copie = alocare(v2[i1], v3[i1]);
		for (int i = 0; i < v2[i1]; i++)
			for (int j = 0; j < v3[i1]; j++) { // fac matricea In
				if (i == j)
					p[i][j] = 1;
				else
					p[i][j] = 0;
				copie[i][j] = 0;
			} //am nevoie de matricea unitate pentru a face inmultirea
			//in timp logaritmic
		while (pow) {
			if (pow % 2 == 1) {
				for (int i = 0; i < v2[i1]; i++)
					for (int j = 0; j < v3[i1]; j++)
						inmultire(copie, p, v1[i1], i, j, v3[i1]);
			for (int i = 0; i < v2[i1]; i++)
				for (int j = 0; j < v3[i1]; j++) {
					p[i][j] = copie[i][j];
					copie[i][j] = 0;//daca puterea este impara voi inmulti
					//matricea p cu matricea data
				}
			}
			for (int i = 0; i < v2[i1]; i++)
				for (int j = 0; j < v3[i1]; j++)
					inmultire(copie, v1[i1], v1[i1], i, j, v2[i1]);
			for (int i = 0; i < v2[i1]; i++)
				for (int j = 0; j < v3[i1]; j++) {
					v1[i1][i][j] = copie[i][j];
					copie[i][j] = 0;
				} //ridic la patrat matricea data
			pow = pow / 2;//impart la 2 puterea si iau catul
			//operatia se reia p ramanan p = p * a iar a = a * a;
		}
		for (int i = 0; i < v2[i1]; i++)
			for (int j = 0; j < v3[i1]; j++)
				v1[i1][i][j] = p[i][j];
		for (int i = 0; i < v2[i1]; i++) {
			free(p[i]);
			free(copie[i]);
		}
		free(p);
		free(copie);
}

void eliberare(int ****vect_index, int **v1, int **v2, int *indice, int i1)
{
	if (i1 > *indice - 1 || i1 < 0) { //verificare
		printf("No matrix with the given index\n");
	} else {
	    for (int i = i1; i < (*indice) - 1; i++) { //interschimb pozitiile
		//adreselor punand-o pe cea data pe ultimul loc
			int **aux = (*vect_index)[i];
		    (*vect_index)[i] = (*vect_index)[i + 1];
			(*vect_index)[i + 1] = aux;
			int aux1 = (*v1)[i];
		    (*v1)[i] = (*v1)[i + 1];
			(*v1)[i + 1] = aux1;
		    (*v2)[i] = (*v2)[i + 1];
	    }
		for (int i = 0; i < (*v1)[(*indice) - 1]; i++)
			free((*vect_index)[(*indice) - 1][i]);
		free((*vect_index)[(*indice) - 1]);
		(*indice) = (*indice) - 1;//eliberez ultimul element, matricea
		//pe care o voiam stearsa
	}
}

void eliberare_fortata(int ***vect_index, int *v1, int *v2, int indice)
{
	for (int i = 0; i < indice; i++) {
		for (int j = 0; j < v1[i]; j++)
			free(vect_index[i][j]);
		free(vect_index[i]);
	}
	free(vect_index);
	free(v1);
	free(v2);
	//eliberez tot sirul de matrici
}
