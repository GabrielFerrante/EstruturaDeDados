#include <stdio.h>
#include <stdlib.h>

//SOMA DAS LINHAS
int sum_of_matrix(int **matriz, int linhas, int colunas){
	int i = 0;    // ----------------------------------------------------------1
	int soma = 0; // ----------------------------------------------------------1
	for(i = 0; i < linhas; i++){ // -------------------------------------------SOMAT�RIO - LS: N, LI: i = 1, TERMO: 1 + 1 + N + 1
		int j = 0; // ---------------------------------------------------1
		int soma_linha = 0;// -------------------------------------------1
		for(j=0; j < colunas; j++){ // ----------------------------------SOMAT�RIO - LS: N, LI: i = 1, TERMO: 1 (ISSO EQUIVALE A N)
			soma_linha = soma_linha + matriz[i][j]; // --------------1
		}
		soma = soma + soma_linha; // -----------------------------------1
		printf("Soma da linha %d - %d\n", i, soma_linha);
	}
	return soma;
}
// AO FINAL, � POSSIVEL DESTRINCHAR EM 4 SOMAT�RIOS DISTINTOS O LOOP DE LINHAS
// 1� SOMAT�RIO - LS: N, LI: i = 1, TERMO: 1 (ou seja, N)
// 2� SOMAT�RIO - LS: N, LI: i = 1, TERMO: 1 (ou seja, N)
// 3� SOMAT�RIO - LS: N, LI: i = 1, TERMO: N (ou seja, n+n+n+n.... vezes N), logo, n� (n ao quadrado). Loop de colunas e a soma linha.
// 4� SOMAT�RIO - LS: N, LI: i = 1, TERMO: 1 (ou seja, N)

// T(n) = n� + 3n + 2 (esse dois, que vem antes dos loops)
//Pegando o maior termo, temos, Big O(n�)

void main(){
	
	int LINHAS = 4;
	int COLUNAS = 4;
	//VAMOS USAR UMA MATRIZ QUADRADA
	
	int **matriz = (int **)malloc(LINHAS * sizeof(int *));

	//malloc(LINHAS * sizeof(int *)) Aloca mem�ria suficiente para armazenar LINHAS ponteiros para inteiros
	//(int **)- Faz um cast do ponteiro gen�rico retornado por malloc para um ponteiro para ponteiro de inteiro
	//int **matriz: Declara uma vari�vel que ser� um array de ponteiros, onde cada ponteiro apontar� para uma linha da matriz
	// Seria como se fosse - matriz [ponteiro0, ponteiro1, ponteiro2, ..., ponteiroLINHAS-1]
	
	int i = 0;
	for (i = 0; i < LINHAS; i++){
		matriz[i] = (int *)malloc(COLUNAS * sizeof(int));
		//malloc(COLUNAS * sizeof(int))- Aloca mem�ria para uma linha da matriz com COLUNAS elementos inteiros
		//(int *)- Faz cast do ponteiro gen�rico para ponteiro para inteiro
		//matriz[i]- Atribui o ponteiro alocado ao i-�simo elemento do array de ponteiros
	}
	
	printf("digite os numeros\n");
	i = 0;
	int j = 0;
	for(i = 0; i < LINHAS; i++ ){
		
		for (j = 0; j < COLUNAS; j++){
			printf("DIGITE O VALOR NA POSICAO %d,%d = ", i, j);
			scanf("%d", &matriz[i][j]);
		}
		printf("\n");
	}
	
	int soma = sum_of_matrix(matriz, LINHAS, COLUNAS);
	printf("SOMA FINAL : %d\n",soma);
	
	system("PAUSE");
   	
	
}
