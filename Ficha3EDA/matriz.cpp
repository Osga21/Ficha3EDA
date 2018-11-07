#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

Matriz::Matriz(int nLinhas, int nColunas)
{
	Iniciar(nLinhas, nColunas);
}

Matriz::Matriz() { //construtor por omissão

	Iniciar(0, 0);
}

Matriz::~Matriz() //destrutor
{
	Apagar();
}

Matriz::Matriz(const Matriz & m1) //construtor copia
{
	Iniciar(m1.nlinhas, m1.ncols);
	for (int i = 0; i < m1.nlinhas; i++) {
		for (int j = 0; j < m1.ncols; j++) {
			elems[i][j] = m1.elems[i][j];
		}
	}
}

void Matriz::Apagar()
{
	for (int i = 0; i < nlinhas; i++) {
		delete[] elems[i];
	}
	delete[] elems;
}

void Matriz::Iniciar(int l, int c) {
	nlinhas = l;
	ncols = c;
	elems = new float*[nlinhas];
	for (int i = 0; i < nlinhas; i++) { //alocação de memória
		elems[i] = new float[ncols];
	}

	for (int i = 0; i < nlinhas; i++) {
		for (int j = 0; j < ncols; j++) { //inicialização
			elems[i][j] = 0;
		}
	}
}

bool Matriz::Ler(const char *nome_ficheiro)
{
	FILE *ficheiro;
	ficheiro = fopen(nome_ficheiro, "r");
	if (ficheiro == NULL)
		return false;
	else {
		Apagar();
		fscanf(ficheiro, "%d %d", &nlinhas, &ncols);
		Iniciar(nlinhas, ncols);
		for (int i = 0; i < nlinhas; i++) {
			for (int j = 0; j < ncols; j++) { //inicialização
				fscanf(ficheiro, "%f", &elems[i][j]);
			}
		}
		return true;
	}
}

void Matriz::Escrever()
{
	for (int i = 0; i < nlinhas; i++) {
		for (int j = 0; j < ncols; j++) { //inicialização
			printf(" %g\t", elems[i][j]);
		}
		printf("\n");
	}

}

bool Matriz::PodeMultiplicar(const Matriz * pm)
{
	if (ncols == pm->nlinhas) 
		return true;
	else
		return false;
}

bool Matriz::PodeSomar(const Matriz * pm)
{
	if (ncols == pm->ncols && nlinhas == pm->nlinhas)
		return true;
	return false;
}

const Matriz Matriz::operator=(const Matriz & m1)
{
	Apagar();
	Iniciar(m1.nlinhas, m1.ncols);
	for (int i = 0; i < m1.nlinhas; i++) {
		for (int j = 0; j < m1.ncols; j++) {
			elems[i][j] = m1.elems[i][j];
		}
	}
	return *this;
}

Matriz Matriz::operator+(const Matriz & m1)
{
	/*Devole soma de duas matrizes, devolve matriz nula
	caso não seja possivel fazer a soma(ver PodeSomar)*/
	Matriz m2;
	m2 = *this;

	if (m2.PodeSomar(&m1)) {

		Apagar();
		Iniciar(m1.nlinhas, m1.ncols);
		for (int i = 0; i < m1.nlinhas; i++) {
			for (int j = 0; j < m1.ncols; j++) {
				elems[i][j] = m1.elems[i][j] + m2.elems[i][j];
			}
		}
		return *this;
	}
	else{
		Matriz m0(nlinhas, ncols);
		return m0;
	}
	
}

Matriz Matriz::operator*(const Matriz & m1)
{
	Matriz m2;
	m2 = *this;

	if(m2.PodeMultiplicar(&m2))
	Apagar();
	Iniciar(m2.nlinhas, m1.ncols);
	for (int i = 0; i < m2.nlinhas; i++) {
		for (int j = 0; j < m1.ncols; j++) {
			elems[i][j]=0;
			for (int k = 0; k < m2.ncols; k++) {
				elems[i][j] +=m2.elems[i][k] * m1.elems[k][j];
			}
		}
	}
	return *this;
}

Matriz Matriz::DecomporLU()
{
	/*Devolve decomposta LU caso a matriz seja quadrada,
	devolve matriz nula se não for quadrada*/

	Matriz LU(nlinhas, ncols); //Matriz nula

	if (nlinhas == ncols) {
		Matriz L(nlinhas, nlinhas);
		Matriz U(nlinhas, nlinhas);
		for (int i = 0; i < nlinhas; i++) { //Cálculo da upper
			for (int j = i; j < nlinhas; j++) {

				float sum = 0;
				for (int k = 0; k < i; k++) {

					sum += (L.elems[i][k] * U.elems[k][j]);
				}

				U.elems[i][j] = elems[i][j] - sum;
			}

			for (int j = i; j < nlinhas; j++) { //Calculo da lower
				if (i == j)
					L.elems[i][i] = 1; // Diagonal da matriz lower a 1
				else {
					float sum = 0;
					for (int k = 0; k < i; k++)
						sum += (L.elems[j][k] * U.elems[k][i]);
					L.elems[j][i] = (elems[j][i] - sum) / U.elems[i][i];
				}
			}
		}
		//Junção upper e lower
		LU = U;
		for (int i = 0; i < nlinhas; i++) {
			for (int j = 0; j < nlinhas; j++) {
				if (LU.elems[i][j] == 0)
					LU.elems[i][j] = L.elems[i][j];
			}
		}
		return LU;
	}

	else
		return LU;
}

float Matriz::calcularDet()
/*Apenas para matrizes quadradas, baseado em DecomporLU*/
{
	float det = 1;
	for (int i = 0; i < nlinhas; i++) {
		for (int j = 0; j < ncols; j++) {
			if (i == j) {
				det *= elems[i][j];
			}
		}
	}
	
	return det;
}

Matriz Matriz::obterInversa()
{	
	Matriz LU= DecomporLU();
	Matriz Y(nlinhas,ncols);
	Matriz B(nlinhas, ncols);
	B = Y;
	for (int i = 0; i < nlinhas;i++) {//Calculo de Y
		for (int n = 0; n < ncols;n++) {
			float soma = 0;
			for (int k = 0; k < i; k++) {
				soma+=LU.elems[i][k] * Y.elems[k][n];
			}
			Y.elems[i][n] = (i == n) ?  1 - soma : -soma;
		}
	}

	for (int i = nlinhas-1; i >=0 ; i--) {//Calculo de Y
		for (int n = 0; n < ncols; n++) {
			float soma = 0;
			for (int k = i+1; k < nlinhas; k++) {
				soma += LU.elems[i][k] * B.elems[k][n];
				B.elems[i][n] = (1 / LU.elems[i][i])*(Y.elems[i][n] - soma);
			}
		}
	}
	
	B.Escrever();
	return Matriz();
}




