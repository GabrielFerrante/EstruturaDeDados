#include <stdio.h>
#include <stdlib.h>

// Primeiro, precisamos de uma fun��o de troca.
// Note que, quando selecionamos para troca, duas posi��es do array, estamos tendo um problema N-2, ao inv�s de N
void swap(int*L, int a, int b){
	int temp;
	temp = L[a]; //-----------------------1
	L[a] = L[b]; //-----------------------1
	L[b] = temp; //-----------------------1
	
}
// Note que a fun��o � simples, com complexidade Big O(1)
//Para fazer a invers�o de forma recursiva, precisamos entender a condi��o de parada.
// Temos que ter o index do fim <= o index do inicio, lembrando, o fim � iniciado pela ultima posi��o do array e inicio � o primeiro index

void insert(int *L, int inicio, int fim){
	printf("Inicio : %d | Fim : %d\n", inicio, fim);
	
	if(fim <= inicio){
		printf("Fim da recursao\n");
	}else{
		printf("%d e %d\n", L[inicio], L[fim]);
		swap(L, inicio, fim); // ------------ Big O(1)
		insert(L, inicio+1, fim-1);
	}
}

//Calculando a complexidade
// T(n) = T(n-2) + O(1) (ou seja 1)
// Abrindo recorr�ncia de T(n-2)
// T(n) = T(n-4) + 1 + 1, note que � "n-4", pois cada itera��o, s�o sempre menos 2 numeros da lista.
// T(n) = T(n-6) + 1 + 1 + 1
//Entendendo o padr�o:
//O n�mero de somas de 1, � igual a k, no caso, k = 3
//O n�mero de redu��o de n, ou seja, n-6, 6 � igual a 2.k.
//Para um K arbitr�rio temos:
//T(n) = T(n-2.k) + k.1
//Na condi��o de parada, onde T(0) tem que ser:
//Para n-2.k = 0, o "n" tem que ser "2.k" e "k" tem que ser "n/2"
//Portando,
//T(n) = T(0) + (n/2) . 1
//T(n) = 1 + (n/2) . 1
//Complexidade de Big O(n)


void main(){
	int arr[8] = {27,0,3,3,25,6,22,10};
	int tamanho = sizeof(arr) / sizeof(arr[0]);
	printf("Lista inicial\n");
	int i=0;
	for(i=0; i < tamanho; i++){
		printf("%d,", arr[i]);
	}
	printf("\n");
	insert(arr, 0, tamanho-1); // Tamanho-1 por que quando � calculado, ele considera 8, mas os indexes v�o at� 7
	i=0;
	printf("Lista final\n");
	for(i=0; i < tamanho; i++){
		printf("%d,", arr[i]);
	}
	printf("\n");
	
	system("PAUSE");
	
}
