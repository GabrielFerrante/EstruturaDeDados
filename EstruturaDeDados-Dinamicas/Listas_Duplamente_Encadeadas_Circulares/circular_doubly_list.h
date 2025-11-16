#ifndef CIRCULAR_DOUGLY_LIST_H
#define CIRCULAR_DOUGLY_LIST_H

typedef struct Node {
    int key;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} CircularList;

void init(CircularList* cl);
void add_head(CircularList* cl, int key);
void add_tail(CircularList* cl, int key);
Node* search(CircularList* cl, int key);
void add_between(CircularList* cl, int after_key, int new_key);
int remove_node(CircularList* cl, int key);
void display_forward(CircularList* cl);
void display_backward(CircularList* cl);
void free_list(CircularList* cl);

#endif
