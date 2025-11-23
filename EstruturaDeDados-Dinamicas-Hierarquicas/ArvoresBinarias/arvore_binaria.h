#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
} No;

No* criar_no(int valor);
void inserir(No** raiz, int valor);
void pre_ordem(No* raiz);
void em_ordem(No* raiz);
void pos_ordem(No* raiz);
No* buscar(No* raiz, int valor);
void liberar_arvore(No* raiz);

#endif
