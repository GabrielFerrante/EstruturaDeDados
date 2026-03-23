

#include <stdio.h>    
#include "heapsort.h" 

// PRIMITIVA SWAP
static void trocar(int *a, int *b) {
	printf("Trocando %d por %d \n", *a, *b);
    int temp = *a;
    *a = *b;
    *b = temp;
}


void heapify(int array[], int tamanho, int raiz) {
    int maior  = raiz;          /* Assume que a raiz e o maior */
    int esq    = 2 * raiz + 1;  /* Indice do filho esquerdo    */
    int dir    = 2 * raiz + 2;  /* Indice do filho direito     */

    /* Verifica se o filho esquerdo existe e se eh maior que a raiz */
    if (esq < tamanho && array[esq] > array[maior]) {
        maior = esq;
    }

    /* Verifica se o filho direito existe e se eh maior que o atual 'maior' */
    if (dir < tamanho && array[dir] > array[maior]) {
        maior = dir;
    }

    /* Se o maior nao for a raiz, precisamos trocar e continuar peneirando */
    if (maior != raiz) {
        trocar(&array[raiz], &array[maior]);

        /* Chama heapify recursivamente na subarvore que foi alterada */
        heapify(array, tamanho, maior); 
    }
    
    
}

void heapSort(int array[], int tamanho) {
    int i;
	
    // CONSTROI O MAX HEAP
    
    for (i = tamanho / 2 - 1; i >= 0; i--) {
        heapify(array, tamanho, i);
    }
   

    // TROCA E HEAPFY
    for (i = tamanho - 1; i > 0; i--) {
     
        trocar(&array[0], &array[i]);
        imprimirArray(array, tamanho);
        heapify(array, i, 0);
    }
    
}

void imprimirArray(int array[], int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
