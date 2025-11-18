#ifndef SPARSE_MATRIX_LINKED_H
#define SPARSE_MATRIX_LINKED_H

#define MAX_ROWS 10
#define MAX_COLS 10

typedef struct Node {
    int row;
    int col;
    int value;
    struct Node* next;
} Node;

typedef struct {
    int rows;
    int cols;
    Node* head;
} SparseMatrixLinked;

// Primitivas principais
void sparse_matrix_encode(int dense_matrix[MAX_ROWS][MAX_COLS], int rows, int cols, SparseMatrixLinked *sparse);
void sparse_matrix_decode(SparseMatrixLinked *sparse, int dense_matrix[MAX_ROWS][MAX_COLS]);

// Funções auxiliares
Node* create_node(int row, int col, int value);
void insert_node(SparseMatrixLinked *sparse, int row, int col, int value);
void free_list(SparseMatrixLinked *sparse);
void print_sparse_linked(SparseMatrixLinked *sparse);
void print_dense_matrix(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols);

#endif
