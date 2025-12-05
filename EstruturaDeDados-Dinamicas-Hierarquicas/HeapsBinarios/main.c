#include <stdio.h>
#include <stdlib.h>
#include "heap.c"
#include <locale.h>

int main() {
	setlocale(LC_ALL, "portuguese");
    printf("=== HEAPS BINÁRIOS E HEAPSORT ===\n\n");
    
    // Teste 1: Max-Heap
    printf("1. TESTE MAX-HEAP\n");
    printf("-----------------\n");
    
    Heap* max_heap = criar_heap(10, 1); // 1 para max-heap
    
    printf("Inserindo elementos: 10, 20, 15, 30, 40\n");
    inserir(max_heap, 10);
    inserir(max_heap, 20);
    inserir(max_heap, 15);
    inserir(max_heap, 30);
    inserir(max_heap, 40);
    
    imprimir_heap(max_heap);
    
    printf("\nExtraindo raiz (maior elemento): %d\n", extrair_raiz(max_heap));
    printf("Heap após extração: ");
    int i;
    for (i = 0; i < max_heap->size; i++) {
        printf("%d ", max_heap->arr[i]);
    }
    printf("\n\n");
    
    // Teste 2: Min-Heap
    printf("2. TESTE MIN-HEAP\n");
    printf("-----------------\n");
    
    Heap* min_heap = criar_heap(10, 0); // 0 para min-heap
    
    printf("Inserindo elementos: 40, 30, 15, 20, 10\n");
    inserir(min_heap, 40);
    inserir(min_heap, 30);
    inserir(min_heap, 15);
    inserir(min_heap, 20);
    inserir(min_heap, 10);
    
    imprimir_heap(min_heap); //Lembre-se que, 40 e 20, são filhos de 15
    
    printf("\nExtraindo raiz (menor elemento): %d\n", extrair_raiz(min_heap));
    printf("Heap após extração: ");
    for (i = 0; i < min_heap->size; i++) {
        printf("%d ", min_heap->arr[i]);
    }
    printf("\n\n");
    
    // Teste 3: Heapsort com Max-Heap (ordenação crescente)
    printf("3. HEAPSORT COM MAX-HEAP (ORDENAÇÃO CRESCENTE)\n");
    printf("--------------------------------------------\n");
    
    int arr_crescente[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr_crescente) / sizeof(arr_crescente[0]);
    
    printf("Array original: ");
    imprimir_array(arr_crescente, n);
    
    heapsort(arr_crescente, n, 1); // 1 para max-heap (crescente)
    
    printf("Array ordenado (crescente): ");
    imprimir_array(arr_crescente, n);
    printf("\n");
    
    // Teste 4: Heapsort com Min-Heap (ordenação decrescente)
    printf("4. HEAPSORT COM MIN-HEAP (ORDENAÇÃO DECRESCENTE)\n");
    printf("-----------------------------------------------\n");
    
    int arr_decrescente[] = {12, 11, 13, 5, 6, 7};
    int m = sizeof(arr_decrescente) / sizeof(arr_decrescente[0]);
    
    printf("Array original: ");
    imprimir_array(arr_decrescente, m);
    
    heapsort(arr_decrescente, m, 0); // 0 para min-heap (decrescente)
    
    printf("Array ordenado (decrescente): ");
    imprimir_array(arr_decrescente, m);
    printf("\n");
    
    // Teste 5: Comparação dos dois métodos
    printf("5. COMPARAÇÃO DOS DOIS MÉTODOS\n");
    printf("------------------------------\n");
    
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int arr2[] = {64, 34, 25, 12, 22, 11, 90};
    int tamanho = sizeof(arr1) / sizeof(arr1[0]);
    
    printf("Array original: ");
    imprimir_array(arr1, tamanho);
    
    // Heapsort crescente (max-heap)
    heapsort(arr1, tamanho, 1);
    printf("Heapsort crescente (max-heap): ");
    imprimir_array(arr1, tamanho);
    
    // Heapsort decrescente (min-heap)
    heapsort(arr2, tamanho, 0);
    printf("Heapsort decrescente (min-heap): ");
    imprimir_array(arr2, tamanho);
    
    // Teste 6: Heap a partir de array existente
    printf("\n6. CONSTRUINDO HEAP A PARTIR DE ARRAY EXISTENTE\n");
    printf("----------------------------------------------\n");
    
    int dados[] = {3, 9, 2, 1, 4, 5};
    int tam_dados = sizeof(dados) / sizeof(dados[0]);
    
    // Criar max-heap com array existente
    Heap* heap_array = criar_heap(tam_dados, 1);
    heap_array->size = tam_dados;
    for (i = 0; i < tam_dados; i++) {
        heap_array->arr[i] = dados[i];
    }
    
    printf("Array antes de construir heap: ");
    imprimir_array(dados, tam_dados);
    
    construir_heap(heap_array);
    printf("Max-heap construído: ");
    imprimir_heap(heap_array);
    
    // Liberar memória
    destruir_heap(max_heap);
    destruir_heap(min_heap);
    destruir_heap(heap_array);
    
    printf("\nTodos os heaps foram destruídos. Fim do programa.\n");
    
    return 0;
}
