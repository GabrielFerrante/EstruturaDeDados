#include "sparse_matrix_linked.h"
#include <stdio.h>
#include <stdlib.h>

Node* create_node(int row, int col, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }
    new_node->row = row;
    new_node->col = col;
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void insert_node(SparseMatrixLinked *sparse, int row, int col, int value) {
    Node* new_node = create_node(row, col, value);
    
    if (sparse->head == NULL) {
        // Lista vazia
        sparse->head = new_node;
        return;
    }
    
    // Inserção ordenada por linha e coluna
    Node* current = sparse->head;
    Node* previous = NULL;
    
    //Método sem ponteiro no final, ou seja, torna a inserção no pior caso O(n)
    while (current != NULL) {
        // Encontra a posição correta (ordenado por linha, depois por coluna)
        if (current->row > row || (current->row == row && current->col > col)) {
            break;
        }
        previous = current;
        // andando até a cabeça
        current = current->next;
    }
    
    if (previous == NULL) {
        // Inserir no início
        new_node->next = sparse->head;
        sparse->head = new_node;
    } else {
        // Inserir no meio ou final
        new_node->next = current;
        previous->next = new_node;
    }
}

void sparse_matrix_encode(int dense_matrix[MAX_ROWS][MAX_COLS], int rows, int cols, SparseMatrixLinked *sparse) {
    sparse->rows = rows;
    sparse->cols = cols;
    sparse->head = NULL;
    
    int i = 0;
    int j = 0;
    // Percorre a matriz densa procurando elementos não-zero
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (dense_matrix[i][j] != 0) {
                insert_node(sparse, i, j, dense_matrix[i][j]);
            }
        }
    }
}

void sparse_matrix_decode(SparseMatrixLinked *sparse, int dense_matrix[MAX_ROWS][MAX_COLS]) {
	int i = 0;
	int j = 0;
    // Inicializa a matriz densa com zeros
    for (i = 0; i < sparse->rows; i++) {
        for ( j = 0; j < sparse->cols; j++) {
            dense_matrix[i][j] = 0;
        }
    }
    
    // Preenche os elementos não-zero baseado na lista encadeada
    Node* current = sparse->head;
    while (current != NULL) {
        dense_matrix[current->row][current->col] = current->value;
        current = current->next;
    }
}

void free_list(SparseMatrixLinked *sparse) {
    Node* current = sparse->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    sparse->head = NULL;
}

void print_sparse_linked(SparseMatrixLinked *sparse) {
    printf("Matriz Esparsa (Lista Encadeada):\n");
    printf("Linhas: %d, Colunas: %d\n", sparse->rows, sparse->cols);
    printf("Row\tColumn\tValue\n");
    
    Node* current = sparse->head;
    while (current != NULL) {
        printf("%d\t%d\t%d\n", current->row, current->col, current->value);
        current = current->next;
    }
}

void print_dense_matrix(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
    printf("Matriz Densa:\n");
    int i = 0;
    int j = 0;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}
