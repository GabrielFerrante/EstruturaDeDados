#ifndef ABB_H
#define ABB_H

typedef struct No {
    int valor;
    struct No* esq;
    struct No* dir;
} No;

No* criar_no(int valor);
No* inserir(No* raiz, int valor);
No* buscar(No* raiz, int valor);
No* remover(No* raiz, int valor);
void em_ordem(No* raiz);
No* menor_valor(No* raiz);
void liberar(No* raiz);

#endif
