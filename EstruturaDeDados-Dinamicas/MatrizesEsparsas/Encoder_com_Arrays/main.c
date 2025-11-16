#include <stdio.h>
#include "sparse_matrix.c"
#include <locale.h>

int main() {
	setlocale(LC_ALL, "portuguese");
    // Matriz densa de exemplo (8x8 com poucos elementos não-zero)
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
    
    printf("=== MATRIZ ESPARSA - DEMONSTRAÇÃO ===\n\n");
    
    // Exibe a matriz densa original
    printf("1. Matriz Densa Original:\n");
    print_dense_matrix(dense_matrix, rows, cols);
    printf("\n");

    // Codifica para formato esparso
    SparseMatrix sparse;
    sparse_matrix_encode(dense_matrix, rows, cols, &sparse);
    
    printf("2. Matriz Codificada em Formato Esparsa:\n");
    print_sparse_matrix(&sparse);
    printf("\n");

    // Decodifica de volta para matriz densa
    int decoded_matrix[MAX_ROWS][MAX_COLS];
    sparse_matrix_decode(&sparse, decoded_matrix);
    
    printf("3. Matriz Decodificada (de volta ao formato denso):\n");
    print_dense_matrix(decoded_matrix, rows, cols);
    printf("\n");

    // Exemplo com mais elementos
    printf("4. Outro Exemplo - Matriz 4x4:\n");
    int dense2[MAX_ROWS][MAX_COLS] = {
        {1, 0, 0, 0},
        {0, 0, 2, 0},
        {0, 3, 0, 0},
        {0, 0, 0, 4}
    };
    
    SparseMatrix sparse2;
    sparse_matrix_encode(dense2, 4, 4, &sparse2);
    
    printf("Matriz Densa:\n");
    int i = 0;
    for (i = 0; i < 4; i++) {
    	int j = 0;
        for (j = 0; j < 4; j++) {
            printf("%d\t", dense2[i][j]);
        }
        printf("\n");
    }
    
    printf("\nFormato Esparsa:\n");
    print_sparse_matrix(&sparse2);

    return 0;
}
