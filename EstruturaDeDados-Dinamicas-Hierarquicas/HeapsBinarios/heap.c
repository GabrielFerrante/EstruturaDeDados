#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

// Funções auxiliares internas
int pai(int i) { 
	return (i - 1) / 2; 
}
int filho_esquerdo(int i) {
 	return 2 * i + 1; 
}
int filho_direito(int i) {
 	return 2 * i + 2; 
}

Heap* criar_heap(int capacity, int is_max_heap) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->arr = (int*)malloc(capacity * sizeof(int));
    h->size = 0;
    h->capacity = capacity;
    h->is_max_heap = is_max_heap;
    return h;
}

void destruir_heap(Heap* h) {
    free(h->arr);
    free(h);
}

void trocar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap* h, int i) {
    int maior_ou_menor = i;
    int esq = filho_esquerdo(i);
    int dir = filho_direito(i);
    
    if (h->is_max_heap) { // MAX-HEAP
        if (esq < h->size && h->arr[esq] > h->arr[maior_ou_menor])
            maior_ou_menor = esq;
        if (dir < h->size && h->arr[dir] > h->arr[maior_ou_menor])
            maior_ou_menor = dir;
    } else { // MIN-HEAP
        if (esq < h->size && h->arr[esq] < h->arr[maior_ou_menor])
            maior_ou_menor = esq;
        if (dir < h->size && h->arr[dir] < h->arr[maior_ou_menor])
            maior_ou_menor = dir;
    }
    
    if (maior_ou_menor != i) {
        trocar(&h->arr[i], &h->arr[maior_ou_menor]);
        heapify(h, maior_ou_menor);
    }
}

void inserir(Heap* h, int valor) {
    if (h->size == h->capacity) {
        printf("Heap cheio!\n");
        return;
    }
    
    h->arr[h->size] = valor;
    int i = h->size;
    h->size++;
    
    // Ajustar para cima
    if (h->is_max_heap) {
        while (i != 0 && h->arr[pai(i)] < h->arr[i]) {
            trocar(&h->arr[i], &h->arr[pai(i)]);
            i = pai(i);
        }
    } else {
        while (i != 0 && h->arr[pai(i)] > h->arr[i]) {
            trocar(&h->arr[i], &h->arr[pai(i)]);
            i = pai(i);
        }
    }
}

int extrair_raiz(Heap* h) {
    if (h->size <= 0) return -1;
    if (h->size == 1) {
        h->size--;
        return h->arr[0];
    }
    
    int raiz = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    heapify(h, 0);
    
    return raiz;
}

void construir_heap(Heap* h) {
    int inicio = (h->size / 2) - 1;
    int i = inicio;
    for (i = inicio; i >= 0; i--) {
        heapify(h, i);
    }
}

// Funções para Heapsort
void heapify_array(int arr[], int n, int i, int is_max_heap) {
    int maior_ou_menor = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;
    
    if (is_max_heap) { // MAX-HEAP para ordenação crescente
        if (esq < n && arr[esq] > arr[maior_ou_menor])
            maior_ou_menor = esq;
        if (dir < n && arr[dir] > arr[maior_ou_menor])
            maior_ou_menor = dir;
    } else { // MIN-HEAP para ordenação decrescente
        if (esq < n && arr[esq] < arr[maior_ou_menor])
            maior_ou_menor = esq;
        if (dir < n && arr[dir] < arr[maior_ou_menor])
            maior_ou_menor = dir;
    }
    
    if (maior_ou_menor != i) {
        trocar(&arr[i], &arr[maior_ou_menor]);
        heapify_array(arr, n, maior_ou_menor, is_max_heap);
    }
}

void heapsort(int arr[], int n, int is_max_heap) {
    // Construir heap
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        heapify_array(arr, n, i, is_max_heap);
    
    // Extrair elementos um por um
    for (i = n - 1; i > 0; i--) {
        trocar(&arr[0], &arr[i]); // Move a raiz para o final
        heapify_array(arr, i, 0, is_max_heap); // Heapify no heap reduzido
    }
}

void imprimir_heap(Heap* h) {
    printf("Heap (%s): ", h->is_max_heap ? "Max-Heap" : "Min-Heap");
    int i;
    for (i = 0; i < h->size; i++) {
        printf("%d ", h->arr[i]);
    }
    printf("\n");
    
    // Imprimir de forma hierárquica (opcional)
    if (h->size > 0) {
        printf("Estrutura:\n");
        int nivel = 1;
        int contador = 0;
        
        for ( i = 0; i < h->size; i++) {
            printf("%d ", h->arr[i]);
            contador++;
            
            if (contador == nivel) {
                printf("\n");
                nivel *= 2;
                contador = 0;
            } else if (i < h->size - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void imprimir_array(int arr[], int n) {
	int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
