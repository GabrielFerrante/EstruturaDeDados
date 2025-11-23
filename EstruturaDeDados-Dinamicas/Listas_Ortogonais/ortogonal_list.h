#ifndef ORTOGONAL_LIST_H
#define ORTOGONAL_LIST_H

typedef struct OLnode {
    int key;
    struct OLnode* up;
    struct OLnode* down;
    struct OLnode* right;
    struct OLnode* left;
} OLnode;

typedef struct {
    OLnode* head;
    int size;
} OrtogonalList;

// Primitivas principais
void init(OrtogonalList* list);
void build_ortogonal_list(OrtogonalList* list, int** matrix, int rows, int cols);
void traverse_ortogonal_list(OrtogonalList* list);

// Funções auxiliares
OLnode* create_node(int key);
void insert_node(OrtogonalList* list, int row, int col, int key, int** matrix, int rows, int cols);
void free_ortogonal_list(OrtogonalList* list);
void display_as_dense(OrtogonalList* list, int rows, int cols);

#endif
