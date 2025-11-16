#include "sparse_matrix.h"
#include <stdio.h>

void sparse_matrix_encode(int dense_matrix[MAX_ROWS][MAX_COLS], int rows, int cols, SparseMatrix *sparse) {
    sparse->rows = rows;
    sparse->cols = cols;
    sparse->non_zero = 0;
	int i = 0;
	int j = 0;
    // Percorre a matriz densa procurando elementos não-zero
    for (i = 0; i < rows; i++) {
    	
        for (j = 0; j < cols; j++) {
            if (dense_matrix[i][j] != 0) {
                if (sparse->non_zero < MAX_SIZE) {
                    sparse->data[sparse->non_zero].row = i;
                    sparse->data[sparse->non_zero].col = j;
                    sparse->data[sparse->non_zero].value = dense_matrix[i][j];
                    sparse->non_zero++;
                    
                } else {
                    printf("Erro: Limite máximo de elementos não-zero atingido!\n");
                    return;
                }
            }
        }
    }
}

void sparse_matrix_decode(SparseMatrix *sparse, int dense_matrix[MAX_ROWS][MAX_COLS]) {
	int i = 0;
    // Inicializa a matriz densa com zeros
    for (i = 0; i < sparse->rows; i++) {
    	int j = 0;
        for (j = 0; j < sparse->cols; j++) {
            dense_matrix[i][j] = 0;
        }
    }
    int k = 0;
    // Preenche os elementos não-zero nas posições corretas
    for (k = 0; k < sparse->non_zero; k++) {
        int i = sparse->data[k].row;
        int j = sparse->data[k].col;
        dense_matrix[i][j] = sparse->data[k].value;
    }
}

void print_sparse_matrix(SparseMatrix *sparse) {
    printf("Matriz Esparsa (Formato RCV):\n");
    printf("Linhas: %d, Colunas: %d, Não-zero: %d\n", sparse->rows, sparse->cols, sparse->non_zero);
    printf("Row\tColumn\tValue\n");
    int i = 0;
    for (i = 0; i < sparse->non_zero; i++) {
        printf("%d\t%d\t%d\n", sparse->data[i].row, sparse->data[i].col, sparse->data[i].value);
    }
}

void print_dense_matrix(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
    printf("Matriz Densa:\n");
    int i = 0;
    for (i = 0; i < rows; i++) {
    	int j = 0;
        for (j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}
