#include "ortogonal_list.h"
#include <stdlib.h>
#include <stdio.h>

void init(OrtogonalList* list) {
    list->head = NULL;
    list->size = 0;
}

OLnode* create_node(int key) {
    OLnode* new_node = (OLnode*)malloc(sizeof(OLnode));
    if (new_node == NULL) {
        printf("Erro ao alocar memória para nó!\n");
        return NULL;
    }
    new_node->key = key;
    new_node->up = NULL;
    new_node->down = NULL;
    new_node->right = NULL;
    new_node->left = NULL;
    return new_node;
}

void insert_node(OrtogonalList* list, int row, int col, int key, int** matrix, int rows, int cols) {
    OLnode* new_node = create_node(key);
    if (new_node == NULL) return;
    
    list->size++;
    
    // Caso da lista vazia - criar head
    if (list->head == NULL) {
        list->head = new_node;
        return;
    }
    
    OLnode* current = list->head;
    OLnode* prev_row = NULL;
    OLnode* prev_col = NULL;
    int i = 0;
    int j = 0;
    // Encontrar posição na linha
    while (current != NULL && current->right != NULL) {
        // Encontrar a coluna correta baseada na matriz
        int found = 0;
        for (i = 0; i < rows && !found; i++) {
            for (j = 0; j < cols && !found; j++) {
                if (matrix[i][j] == current->key) {
                    if (i == row && j < col) {
                        prev_row = current;
                        current = current->right;
                        found = 1;
                    } else if (i < row) {
                        prev_row = current;
                        current = current->down;
                        found = 1;
                    }
                }
            }
        }
        if (!found) break;
    }
    
    // Encontrar posição na coluna
    current = list->head;
    while (current != NULL && current->down != NULL) {
        int found = 0;
        for ( i = 0; i < rows && !found; i++) {
            for (j = 0; j < cols && !found; j++) {
                if (matrix[i][j] == current->key) {
                    if (j == col && i < row) {
                        prev_col = current;
                        current = current->down;
                        found = 1;
                    } else if (j < col) {
                        prev_col = current;
                        current = current->right;
                        found = 1;
                    }
                }
            }
        }
        if (!found) break;
    }
    
    // Conectar na linha
    if (prev_row != NULL) {
        new_node->right = prev_row->right;
        if (prev_row->right != NULL) {
            prev_row->right->left = new_node;
        }
        prev_row->right = new_node;
        new_node->left = prev_row;
    }
    
    // Conectar na coluna
    if (prev_col != NULL) {
        new_node->down = prev_col->down;
        if (prev_col->down != NULL) {
            prev_col->down->up = new_node;
        }
        prev_col->down = new_node;
        new_node->up = prev_col;
    }
}

void build_ortogonal_list(OrtogonalList* list, int** matrix, int rows, int cols) {
    init(list);
    int i = 0;
    int j = 0;
    // Primeiro, criar todos os nós e armazenar suas posições
    OLnode*** node_matrix = (OLnode***)malloc(rows * sizeof(OLnode**));
    for (i = 0; i < rows; i++) {
        node_matrix[i] = (OLnode**)malloc(cols * sizeof(OLnode*));
        for (j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                node_matrix[i][j] = create_node(matrix[i][j]);
                list->size++;
            } else {
                node_matrix[i][j] = NULL;
            }
        }
    }
    
    // Conectar os nós
    for (i = 0; i < rows; i++) {
        for ( j = 0; j < cols; j++) {
            if (node_matrix[i][j] != NULL) {
                // Conectar com o nó à direita
                if (j < cols - 1 && node_matrix[i][j + 1] != NULL) {
                    node_matrix[i][j]->right = node_matrix[i][j + 1];
                    node_matrix[i][j + 1]->left = node_matrix[i][j];
                }
                
                // Conectar com o nó abaixo
                if (i < rows - 1 && node_matrix[i + 1][j] != NULL) {
                    node_matrix[i][j]->down = node_matrix[i + 1][j];
                    node_matrix[i + 1][j]->up = node_matrix[i][j];
                }
            }
        }
    }
    
    // Definir o head como o primeiro nó não-nulo (canto superior esquerdo)
    for (i = 0; i < rows; i++) {
        for ( j = 0; j < cols; j++) {
            if (node_matrix[i][j] != NULL) {
                list->head = node_matrix[i][j];
                break;
            }
        }
        if (list->head != NULL) break;
    }
    
    // Liberar a matriz auxiliar
    for (i = 0; i < rows; i++) {
        free(node_matrix[i]);
    }
    free(node_matrix);
}

void traverse_ortogonal_list(OrtogonalList* list) {
    printf("=== TRAVESSIA DA LISTA ORTOGONAL ===\n");
    printf("Tamanho da lista: %d\n\n", list->size);
    
    if (list->head == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    
    // Encontrar o nó do canto superior esquerdo
    OLnode* row_start = list->head;
    while (row_start->left != NULL) row_start = row_start->left;
    while (row_start->up != NULL) row_start = row_start->up;
    
    // Travessia por linhas
    printf("Travessia por Linhas:\n");
    OLnode* current_row = row_start;
    int row_num = 0;
    
    while (current_row != NULL) {
        printf("Linha %d: ", row_num++);
        OLnode* current = current_row;
        
        while (current != NULL) {
            printf("%d", current->key);
            if (current->right != NULL) {
                printf(" -> ");
            }
            current = current->right;
        }
        printf("\n");
        
        // Mover para a próxima linha
        current_row = current_row->down;
    }
    printf("\n");
    
    // Travessia por colunas
    printf("Travessia por Colunas:\n");
    OLnode* col_start = row_start;
    int col_num = 0;
    
    while (col_start != NULL) {
        printf("Coluna %d: ", col_num++);
        OLnode* current = col_start;
        
        while (current != NULL) {
            printf("%d", current->key);
            if (current->down != NULL) {
                printf(" -> ");
            }
            current = current->down;
        }
        printf("\n");
        
        // Mover para a próxima coluna
        col_start = col_start->right;
    }
}

void display_as_dense(OrtogonalList* list, int rows, int cols) {
    printf("Representação como Matriz Densa (%dx%d):\n", rows, cols);
    
    // Criar matriz temporária com zeros
    int** temp_matrix = (int**)malloc(rows * sizeof(int*));
    int i = 0;
    int j = 0;
    for (i = 0; i < rows; i++) {
        temp_matrix[i] = (int*)malloc(cols * sizeof(int));
        for (j = 0; j < cols; j++) {
            temp_matrix[i][j] = 0;
        }
    }
    
    // Preencher com os valores da lista ortogonal
    if (list->head != NULL) {
        // Encontrar o nó do canto superior esquerdo
        OLnode* row_start = list->head;
        while (row_start->left != NULL) row_start = row_start->left;
        while (row_start->up != NULL) row_start = row_start->up;
        
        OLnode* current_row = row_start;
        int current_i = 0;
        
        while (current_row != NULL && current_i < rows) {
            OLnode* current = current_row;
            int current_j = 0;
            
            while (current != NULL && current_j < cols) {
                // Encontrar a posição correta baseada nas conexões
                temp_matrix[current_i][current_j] = current->key;
                current = current->right;
                current_j++;
            }
            
            current_row = current_row->down;
            current_i++;
        }
    }
    
    // Imprimir a matriz
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d\t", temp_matrix[i][j]);
        }
        printf("\n");
    }
    
    // Liberar memória
    for (i = 0; i < rows; i++) {
        free(temp_matrix[i]);
    }
    free(temp_matrix);
}

void free_ortogonal_list(OrtogonalList* list) {
    if (list->head == NULL) return;
    
    // Encontrar o nó do canto superior esquerdo
    OLnode* row_start = list->head;
    while (row_start->left != NULL) row_start = row_start->left;
    while (row_start->up != NULL) row_start = row_start->up;
    
    // Liberar linha por linha
    OLnode* current_row = row_start;
    
    while (current_row != NULL) {
        OLnode* current = current_row;
        OLnode* next_row = current_row->down;
        
        while (current != NULL) {
            OLnode* temp = current;
            current = current->right;
            free(temp);
        }
        
        current_row = next_row;
    }
    
    list->head = NULL;
    list->size = 0;
}
