#include <stdio.h>
#include <stdlib.h>
#include "ortogonal_list.c"
#include <locale.h>

int main() {
	setlocale(LC_ALL, "portuguese");
    OrtogonalList list;
    
    printf("=== LISTAS ORTOGONAIS COM TAD ESPECIFICADA ===\n\n");
    
    // Criar e inicializar matriz 6x6
    int rows = 6, cols = 6;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    int i = 0;
    int j = 0;
    for (i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        for (j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
    
    // Preencher alguns valores não-zero
    matrix[1][1] = 5;
    matrix[3][3] = 8;
    matrix[5][5] = 3;
    matrix[2][4] = 7;
    matrix[4][2] = 9;
    
    printf("1. Matriz Densa Original:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // Construir lista ortogonal
    build_ortogonal_list(&list, matrix, rows, cols);
    printf("2. Lista Ortogonal Construída\n\n");
    
    // Travessia da lista ortogonal
    traverse_ortogonal_list(&list);
    printf("\n");
    
    // Exibir como matriz densa
    display_as_dense(&list, rows, cols);
    printf("\n");
    
    // Outro exemplo - matriz 4x4
    printf("=== OUTRO EXEMPLO - MATRIZ 4x4 ===\n\n");
    
    int rows2 = 4, cols2 = 4;
    int** matrix2 = (int**)malloc(rows2 * sizeof(int*));
    for (i = 0; i < rows2; i++) {
        matrix2[i] = (int*)malloc(cols2 * sizeof(int));
        for (j = 0; j < cols2; j++) {
            matrix2[i][j] = 0;
        }
    }
    
    matrix2[0][0] = 1;
    matrix2[0][3] = 4;
    matrix2[1][2] = 2;
    matrix2[2][1] = 3;
    matrix2[3][0] = 5;
    matrix2[3][3] = 6;
    
    printf("Matriz 4x4 Original:\n");
    for ( i = 0; i < rows2; i++) {
        for ( j = 0; j < cols2; j++) {
            printf("%d\t", matrix2[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    OrtogonalList list2;
    build_ortogonal_list(&list2, matrix2, rows2, cols2);
    
    traverse_ortogonal_list(&list2);
    printf("\n");
    
    display_as_dense(&list2, rows2, cols2);
    
    // Liberar memória
    free_ortogonal_list(&list);
    free_ortogonal_list(&list2);
    
    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    for (i = 0; i < rows2; i++) {
        free(matrix2[i]);
    }
    free(matrix2);
    
    return 0;
}
