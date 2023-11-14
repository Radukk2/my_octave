//#Copyright Constantinescu Radu 313CA 2022-2023
#include <stdio.h>
#include <stdlib.h>

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
		if ((*vect2)[*i1] == (*vect1)[*i2]) {//verificarea posibilitatii e
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

void unrecognized_character(int ch)
{
	int ok = 0;
	if (ch == 'L')
		ok = 1;
	if (ch == 'D')
		ok = 1;
	if (ch == 'P')
		ok = 1;
	if (ch == 'C')
		ok = 1;
	if (ch == 'M')
		ok = 1;
	if (ch == 'O')
		ok = 1;
	if (ch == 'T')
		ok = 1;
	if (ch == 'R')
		ok = 1;
	if (ch == 'F')
		ok = 1;
	if (ch == 'Q')
		ok = 1;
	if (ch == 'S')
		ok = 1;
	if (ok == 0)
		printf("Unrecognized command\n");
		//pentru o litera care nu apartine sirului afisez ca mai sus
}

int main(void)
{
	char ch;
	int m, n, i1, i2, pow, indice = 0, index;
	int ***vect_index, *vect_linii, *vect_coloane;
	vect_index = malloc(0);
	// puncet de start pentru realloc -> nu s-a facut nicio alocare
	vect_linii = malloc(0);
	vect_coloane = malloc(0);
	while (1) {
		scanf(" %c", &ch);
		unrecognized_character(ch);
		//verific ce carecter este ch si actionez intocmai
		if (ch == 'L') {
			index = indice + 1;
			// indexul nou va fi adaugat in matrice,
			//pe cand inidcele este cel al matricei curente
			scanf("%d%d", &m, &n);
			// in continuare va trebuie sa alocam fiecare matrice
			// intr-un vectort pentru a putea avea indexul fiecarei matrice
			vect_index = realloc(vect_index, index * sizeof(int **));
			// adaugam fiecare matrice in vectorul de indexuri
			vect_index[indice] = alocare(m, n);
			citire(vect_index[indice], m, n);
			vect_linii = realloc(vect_linii, index * sizeof(int));
			vect_coloane = realloc(vect_coloane, index * sizeof(int));
			vect_linii[indice] = m;
			//retinem numarul de linii si coloane si doi vectorii
			vect_coloane[indice] = n;
			//folosim vectori pentru ca nu am invatat inca structuri :)
			indice++;
		}
		if (ch == 'D') {
			scanf("%d", &i1);
			determinarea_dimensiunilor(vect_linii, vect_coloane, i1, indice);
		}
		if (ch == 'P') {
			scanf("%d", &i1);
			afisare_matrice(vect_linii, vect_coloane, i1, vect_index, indice);
		}
		if (ch == 'C') {
			scanf("%d", &i1);
			redimensionare(vect_index, vect_linii, vect_coloane, indice, i1);
		}
		if (ch == 'M' || ch == 'S') {
			scanf("%d%d", &i1, &i2);
			mult(&i1, &i2, &vect_index, &vect_linii, &vect_coloane, &indice);
		}
		if (ch == 'O')
			sortare(&vect_index, vect_linii, vect_coloane, indice);
		if (ch == 'T') {
			scanf("%d", &i1);
			transpunere(i1, vect_index, vect_linii, vect_coloane, indice);
		}
		if (ch == 'R') {
			scanf("%d%d", &i1, &pow);
			power(i1, vect_index, vect_linii, vect_coloane, indice, pow);
		}
		if (ch == 'F') {
			scanf("%d", &i1);
			eliberare(&vect_index, &vect_linii, &vect_coloane, &indice, i1);
		}
		if (ch == 'Q') {
			eliberare_fortata(vect_index, vect_linii, vect_coloane, indice);
			break;
		}
	}
	return 0;
}
