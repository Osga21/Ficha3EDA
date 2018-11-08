#define _CRT_SECURE_NO_WARNINGS
#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>
int main(){

	Matriz m4;
	m4.Ler("matriz4.txt");

	printf("\nDeterminante de m4: %g\n", m4.calcularDet());
	Matriz inv;
	inv=m4.obterInversa();

	printf("\nMatriz m4:\n");
	m4.Escrever();

	printf("\nInversa de m4:\n");
	inv.Escrever();

	system("pause");
}