#pragma once
#define _CRT_SECURE_NO_WARNINGS

// Defini��o da classe Matriz que contem as opera��es
// tipicas de matrizes
class Matriz {
	private:
		float **elems;
		int nlinhas;
		int ncols;
		// Fun��es privadas
		void Apagar(); 
		void Iniciar(int nLinhas, int nColunas); 
	public:
		Matriz(); // Construtor de defeito 
		Matriz(const Matriz &m1); // Construtor Copia 
		Matriz(int nLinhas, int nColunas); 
		~Matriz(); // Destrutor DONE
		bool PodeMultiplicar(const Matriz* pm);
		bool PodeSomar(const Matriz* pm);

		const Matriz operator = (const Matriz& m1);
		Matriz operator + (const Matriz& m1);
		Matriz operator * (const Matriz& m1);
		
		bool Ler(const char * nome_ficheiro);
		void Escrever();
		Matriz DecomporLU();
};