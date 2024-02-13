//#Copyright Constantinescu Radu 323CA 2023-2024
// Updated version of last years's homework
#include <stdio.h>
#include <stdlib.h>
#include "matlab_functions.h"

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
			// intr-un vector pentru a putea avea indexul fiecarei matrice
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
		if (ch == 'M') {
			scanf("%d%d", &i1, &i2);
			mult(&i1, &i2, &vect_index, &vect_linii, &vect_coloane, &indice);
		}
		if (ch == 'S') {
			scanf("%d%d", &i1, &i2);
			strassen(&i1, &i2, &vect_index,
					 &vect_linii, &vect_coloane, &indice);
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
