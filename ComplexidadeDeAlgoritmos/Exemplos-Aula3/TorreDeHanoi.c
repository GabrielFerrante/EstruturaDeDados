#include <stdlib.h>
#include <stdio.h>

//Lembrando, estamos calculando o custo para mover a pilha inteira para torre alvo.
int hanoi(int n, char* from, char* to , char* aux){
	
	if(n==0){
		return 0;
	}
	hanoi(n-1, from, aux, to);
	printf("Movendo o disco %d | Mover de: %s para %s\n", n, from, to);
	hanoi(n-1, aux, to, from);
	
}

//O problema de Hanoi � resolver 2 problemas de complexidade n-1
//Logo, 
//T(n) = 2 T(n-1) + O(1), lembrando que O(1) � referente a altera��o dos discos
//Para calcular, temos que usar a rela��o de recorr�ncia
//T(n) = 2[2T(n-2)+1]+1
//T(n) = 2{2[2T(n-3)+1]+1}+1
//Esta ultima T(n) pode ser traduzida como:
//T(n) = 2� T(n-3) + [2� + 2� + 2�], observe que existe um somat�rio de 2 elevado a i, onde i=0 vai at� 2.
//Generalizando, fica:
//T(n) = 2^k T(n-k) + SOMAT�RIO- LS: k-1, LI: i=0, Termo: 2^i
//Vamos nomear o somat�rio como S.
//Iremos utilizar a soma telesc�pica, mas antes entenda: 2^i+1 = 2.2^i = 2^i + 2^i, logo, 2^i = 2^i+1 - 2^i, o que torna telesc�pica.
//S = SOMAT�RIO- LS: k-1, LI: i=0, Termo: (2^i+1 - 2^i)
//Utilizando a t�cnica, os expoentes do LS troca com o da primeira parte da soma e o valor inicial de LI, vira o expoente da segunda parte da soma.
//Resultando em S = 2^k - 1
//Voltando a T(n)
// T(n) = 2^k T(n-k) + 2^k - 1
// Condi��o de parada: k = n
// T(n) = 2^n . T(0) + 2^n - 1
// T(n) = 2^n - 1
// Big O(2^n) 


void main(){
	char torre1[] = "A";
	char torre2[] = "B";
	char torre3[] = "C";
	int n = 3;
	hanoi(n, torre1, torre3, torre2);
	
}
