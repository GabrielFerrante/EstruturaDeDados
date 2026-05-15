#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <stdlib.h>


#define MAX_NIVEL 16

#define PROBABILIDADE 0.5


typedef struct No {
    int valor;
    struct No **frente; /* Array de ponteiros, um por nível */
} No;


typedef struct {
    No  *cabeca;        /* Nó sentinela: não guarda valor útil,
                           apenas serve como ponto de entrada
                           em todos os níveis */
    int  nivel_atual;   /* Nível mais alto ocupado no momento */
    int  tamanho;       /* Número de elementos na lista */
} SkipList;




void sl_inicializar(SkipList *sl);


int sl_nivel_aleatorio(void);


void sl_inserir(SkipList *sl, int valor);


No *sl_buscar(SkipList *sl, int valor);


int sl_remover(SkipList *sl, int valor);


void sl_imprimir(SkipList *sl);


void sl_imprimir_nivel_base(SkipList *sl);


void sl_liberar(SkipList *sl);

#endif 
