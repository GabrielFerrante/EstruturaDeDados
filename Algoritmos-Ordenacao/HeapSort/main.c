
#include <stdio.h>    
#include "heapsort.c" 

int main() {
 	

 	
    int arr[] = {64, 34, 25, 12, 22, 11, 90};

 
    int tamanho = sizeof(arr) / sizeof(arr[0]);

    printf("=== Demonstracao do HeapSort ===\n\n");

    printf("Array original:  ");
    imprimirArray(arr, tamanho);

  
    heapSort(arr, tamanho);

    printf("Array ordenado:  ");
    imprimirArray(arr, tamanho);

    printf("\nOrdenacao concluido com sucesso!\n");

    return 0; 
}
