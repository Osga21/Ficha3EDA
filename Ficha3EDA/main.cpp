#define _CRT_SECURE_NO_WARNINGS
#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>
int main(){
/*
	Matriz m;
	Matriz z;
	Matriz n(3, 3); //usando construtor por defeito

	m.Ler("matriz1.txt");	//matriz usando ficheiro
	z.Ler("matriz2.txt");

	printf("Matriz [M]:\n\n");
	m.Escrever(); //escrita de matriz
	printf("\n");
	printf("Matriz [Z]:\n\n");
	z.Escrever();

	Matriz k;
	Matriz l = m; //Operador =

	k = m*z;//Operador *
	printf("\n");
	printf("Matriz [M]*[Z]:\n\n");
	k.Escrever();
	printf("\n");

	printf("Matriz [M]+[M]:\n\n");

	Matriz s;
	s = l + m;//Operador +
	s.Escrever();

	printf("\nMatriz [T] decomposta:\n\n");//Decomposição LU
	Matriz t,f;
	t.Ler("matrizt.txt");
	f=t.DecomporLU();
	f.Escrever();
*/

	Matriz m3;

	m3.Ler("m3.txt");
	m3 = m3.DecomporLU();
	m3.Escrever();
	printf("\nDeterminante de m3: %g\n",m3.calcularDet());


	system("pause");
}