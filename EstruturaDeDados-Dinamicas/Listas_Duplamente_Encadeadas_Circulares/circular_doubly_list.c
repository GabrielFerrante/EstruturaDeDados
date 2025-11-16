#include "circular_doubly_list.h"
#include <stdlib.h>
#include <stdio.h>

void init(CircularList* cl) {
    cl->head = NULL;
}

void add_head(CircularList* cl, int key) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    
    if (cl->head == NULL) {
        // Lista vazia - o nó aponta para si mesmo
        new_node->next = new_node;
        new_node->prev = new_node;
        cl->head = new_node;
    } else {
        // Lista não vazia - inserir antes do head atual
        Node* tail = cl->head->prev;
        
        new_node->next = cl->head;
        new_node->prev = tail;
        
        cl->head->prev = new_node;
        tail->next = new_node;
        
        cl->head = new_node;
    }
}

void add_tail(CircularList* cl, int key) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    
    if (cl->head == NULL) {
        // Lista vazia - o nó aponta para si mesmo
        new_node->next = new_node;
        new_node->prev = new_node;
        cl->head = new_node;
    } else {
        // Lista não vazia - inserir após a cauda (head->prev)
        Node* tail = cl->head->prev;
        
        new_node->next = cl->head;
        new_node->prev = tail;
        
        tail->next = new_node;
        cl->head->prev = new_node;
    }
}

Node* search(CircularList* cl, int key) {
    if (cl->head == NULL) {
        return NULL;
    }
    
    Node* current = cl->head;
    do {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    } while (current != cl->head);
    
    return NULL;
}

void add_between(CircularList* cl, int after_key, int new_key) {
    Node* target = search(cl, after_key);
    if (target == NULL) {
        printf("Chave %d não encontrada para inserção!\n", after_key);
        return;
    }
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = new_key;
    
    // Inserir após o nó target
    new_node->prev = target;
    new_node->next = target->next;
    
    target->next->prev = new_node;
    target->next = new_node;
}

int remove_node(CircularList* cl, int key) {
    if (cl->head == NULL) {
        return 0;
    }
    
    Node* target = search(cl, key);
    if (target == NULL) {
        return 0;
    }
    
    // Caso especial: remover o único nó da lista
    if (target->next == target && target->prev == target) {
        free(target);
        cl->head = NULL;
        return 1;
    }
    
    // Ajustar os ponteiros dos nós vizinhos
    target->prev->next = target->next;
    target->next->prev = target->prev;
    
    // Se estiver removendo o head, atualizar o head
    if (target == cl->head) {
        cl->head = target->next;
    }
    
    free(target);
    return 1;
}

void display_forward(CircularList* cl) {
    if (cl->head == NULL) {
        printf("Lista vazia\n");
        return;
    }
    
    Node* current = cl->head;
    printf("Lista (frente): ");
    do {
        printf("%d ", current->key);
        current = current->next;
    } while (current != cl->head);
    printf("\n");
}

void display_backward(CircularList* cl) {
    if (cl->head == NULL) {
        printf("Lista vazia\n");
        return;
    }
    
    // Começar da cauda (head->prev)
    Node* current = cl->head->prev;
    printf("Lista (trás): ");
    do {
        printf("%d ", current->key);
        current = current->prev;
    } while (current != cl->head->prev);
    printf("\n");
}

void free_list(CircularList* cl) {
    if (cl->head == NULL) {
        return;
    }
    
    Node* current = cl->head;
    Node* start = cl->head;
    
    do {
        Node* temp = current;
        current = current->next;
        free(temp);
    } while (current != start);
    
    cl->head = NULL;
}
