#include <stdio.h>
#include "sparse_matrix_linked.c"
#include <locale.h>

int main() {
	setlocale(LC_ALL, "portuguese");
    printf("=== MATRIZ ESPARSA COM LISTAS ENCADEADAS ===\n\n");
    
    // Matriz densa de exemplo 8x8
    int dense_matrix[MAX_ROWS][MAX_COLS] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 5, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 8, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    
    int rows = 8, cols = 8;
    
    printf("1. Matriz Densa Original:\n");
    print_dense_matrix(dense_matrix, rows, cols);
    printf("\n");
    
    // Codifica para lista encadeada
    SparseMatrixLinked sparse;
    sparse_matrix_encode(dense_matrix, rows, cols, &sparse);
    
    printf("2. Matriz Codificada em Lista Encadeada:\n");
    print_sparse_linked(&sparse);
    printf("\n");
    
    // Decodifica de volta para matriz densa
    int decoded_matrix[MAX_ROWS][MAX_COLS];
    sparse_matrix_decode(&sparse, decoded_matrix);
    
    printf("3. Matriz Decodificada:\n");
    print_dense_matrix(decoded_matrix, rows, cols);
    printf("\n");
    
    // Teste com matriz mais populada
    printf("4. Outro Exemplo - Matriz 4x4:\n");
    int dense2[MAX_ROWS][MAX_COLS] = {
        {1, 0, 0, 0},
        {0, 0, 2, 0},
        {0, 3, 0, 0},
        {0, 0, 0, 4}
    };
    
    SparseMatrixLinked sparse2;
    sparse_matrix_encode(dense2, 4, 4, &sparse2);
    
    printf("Matriz Densa:\n");
    int i = 0;
    int j = 0;
    for (i = 0; i < 4; i++) {
        for ( j = 0; j < 4; j++) {
            printf("%d\t", dense2[i][j]);
        }
        printf("\n");
    }
    
    printf("\nFormato Lista Encadeada:\n");
    print_sparse_linked(&sparse2);
    
    // Teste de inserção fora de ordem
    printf("\n5. Teste de Inserção Fora de Ordem:\n");
    SparseMatrixLinked sparse3;
    sparse3.rows = 3;
    sparse3.cols = 3;
    sparse3.head = NULL;
    
    // Inserindo elementos fora de ordem
    insert_node(&sparse3, 2, 2, 9);
    insert_node(&sparse3, 0, 0, 1);
    insert_node(&sparse3, 1, 1, 5);
    insert_node(&sparse3, 0, 1, 2);
    
    printf("Lista após inserções fora de ordem (deve estar ordenada):\n");
    print_sparse_linked(&sparse3);
    
    // Liberar memória
    free_list(&sparse);
    free_list(&sparse2);
    free_list(&sparse3);
    
    return 0;
}
