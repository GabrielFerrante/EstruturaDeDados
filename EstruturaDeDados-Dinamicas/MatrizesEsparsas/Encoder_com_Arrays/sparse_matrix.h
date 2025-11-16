#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#define MAX_SIZE 100  // Tamanho máximo para elementos não-zero
#define MAX_ROWS 10   // Número máximo de linhas da matriz original
#define MAX_COLS 10   // Número máximo de colunas da matriz original

typedef struct {
    int row;
    int col;
    int value;
} Element;

typedef struct {
    int rows;
    int cols;
    int non_zero;
    Element data[MAX_SIZE];
} SparseMatrix;

void sparse_matrix_encode(int dense_matrix[MAX_ROWS][MAX_COLS], int rows, int cols, SparseMatrix *sparse);
void sparse_matrix_decode(SparseMatrix *sparse, int dense_matrix[MAX_ROWS][MAX_COLS]);
void print_sparse_matrix(SparseMatrix *sparse);
void print_dense_matrix(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols);

#endif
