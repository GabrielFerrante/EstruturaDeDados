#include <stdio.h>
#include <stdlib.h>

// Cada bucket é uma lista de elementos
typedef struct No {
    int valor;
    struct No* proximo;
} No;

// INSERTION SORT mas pode ser qualquer outro
void inserir_ordenado(No** bucket, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;

    // Se o bucket está vazio ou o valor é menor que o primeiro
    if (*bucket == NULL || (*bucket)->valor >= valor) {
        novo->proximo = *bucket;
        *bucket = novo;
        return;
    }

    // Percorre até achar a posição correta
    No* atual = *bucket;
    while (atual->proximo != NULL && atual->proximo->valor < valor) {
        atual = atual->proximo;
    }
    novo->proximo = atual->proximo;
    atual->proximo = novo;
}

void bucketSort(int array[], int tamanho) {
    if (tamanho <= 0) return;

    
    int max = array[0];
    int i;
    for (i = 1; i < tamanho; i++) {
        if (array[i] > max) max = array[i];
    }

    
    int num_buckets = tamanho;

    
    No** buckets = (No**)calloc(num_buckets, sizeof(No*));

    
    for (i = 0; i < tamanho; i++) {
        // Calcula o índice do bucket para esse elemento
        int indice = (int)((long)array[i] * num_buckets / (max + 1));
        inserir_ordenado(&buckets[indice], array[i]);
    }

    // CONCATENA
    int pos = 0;
    for (i = 0; i < num_buckets; i++) {
        No* atual = buckets[i];
        while (atual != NULL) {
        	printf("Atual concatenado %d\n",atual->valor);
            array[pos++] = atual->valor;
            No* temp = atual;
            atual = atual->proximo;
            free(temp); 
        }
    }

    free(buckets); 
}

void imprimirArray(int array[], int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {42, 32, 33, 52, 37, 47, 51};
    int tamanho = sizeof(arr) / sizeof(arr[0]);

    printf("Array original: ");
    imprimirArray(arr, tamanho);

    bucketSort(arr, tamanho);

    printf("Array ordenado: ");
    imprimirArray(arr, tamanho);

    return 0;
}
