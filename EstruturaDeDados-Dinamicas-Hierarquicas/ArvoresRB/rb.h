#ifndef RB_TREE_H
#define RB_TREE_H
#define VERMELHO 0
#define PRETO    1

/* Nó da árvore */
typedef struct No {
    int valor;
    int cor;           /* VERMELHO ou PRETO */
    struct No *esq;
    struct No *dir;
    struct No *pai;
} No;

typedef struct {
    No *raiz;
    No *nil;  /* nó sentinela: representa todas as folhas NULL */
} ArvoreRB;


ArvoreRB* criar_arvore();
void      inserir(ArvoreRB *t, int valor);
No*       buscar(ArvoreRB *t, int valor);
void      remover(ArvoreRB *t, int valor);
void      imprimir_em_ordem(ArvoreRB *t);
void      liberar(ArvoreRB *t);

#endif
