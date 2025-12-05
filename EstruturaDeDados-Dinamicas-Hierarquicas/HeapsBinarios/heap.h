#ifndef HEAP_H
#define HEAP_H

typedef struct {
    int* arr;
    int size;
    int capacity;
    int is_max_heap; // 1 para max-heap, 0 para min-heap
} Heap;

// Funções básicas de heap
Heap* criar_heap(int capacity, int is_max_heap);
void destruir_heap(Heap* h);
void inserir(Heap* h, int valor);
int extrair_raiz(Heap* h);
void heapify(Heap* h, int i);

// Heapsort
void heapsort(int arr[], int n, int is_max_heap);

// Funções auxiliares
void imprimir_heap(Heap* h);
void imprimir_array(int arr[], int n);
void trocar(int* a, int* b);

#endif
