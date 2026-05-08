#include <stdio.h>
#include <stdlib.h>
#include "rb.h"


static No* criar_no(ArvoreRB *t, int valor) {
    No *no = (No*)malloc(sizeof(No));
    no->valor = valor;
    no->cor   = VERMELHO;
    no->esq   = t->nil;  /* filhos apontam para o sentinela */
    no->dir   = t->nil;
    no->pai   = t->nil;
    return no;
}


static void rotacao_esquerda(ArvoreRB *t, No *x) {
    No *y = x->dir;          /* y é o filho direito de x */

    /* B (filho esquerdo de y) passa a ser filho direito de x */
    x->dir = y->esq;
    if (y->esq != t->nil)
        y->esq->pai = x;

    /* y herda o pai de x */
    y->pai = x->pai;
    if (x->pai == t->nil)
        t->raiz = y;              /* x era raiz */
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;

    /* x passa a ser filho esquerdo de y */
    y->esq = x;
    x->pai = y;
}


static void rotacao_direita(ArvoreRB *t, No *x) {
    No *y = x->esq;

    x->esq = y->dir;
    if (y->dir != t->nil)
        y->dir->pai = x;

    y->pai = x->pai;
    if (x->pai == t->nil)
        t->raiz = y;
    else if (x == x->pai->dir)
        x->pai->dir = y;
    else
        x->pai->esq = y;

    y->dir = x;
    x->pai = y;
}


static void inserir_fixup(ArvoreRB *t, No *z) {
    while (z->pai->cor == VERMELHO) {

        if (z->pai == z->pai->pai->esq) {
            /*Pai é filho ESQUERDO do avô  */
            No *tio = z->pai->pai->dir;

            if (tio->cor == VERMELHO) {
                /* CASO 1: tio vermelho ? só recolorir */
                z->pai->cor      = PRETO;
                tio->cor         = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;   /* sobe para o avô e reavalia */

            } else {
                if (z == z->pai->dir) {
                    /* CASO 2: z é filho direito (triângulo)
                     * ? rotação à esquerda no pai converte em caso 3 */
                    z = z->pai;
                    rotacao_esquerda(t, z);
                }
                /* CASO 3: z é filho esquerdo (linha reta)
                 * ? rotação à direita no avô + recolorir */
                z->pai->cor      = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacao_direita(t, z->pai->pai);
            }

        } else {
            /*  Pai é filho DIREITO do avô */
            No *tio = z->pai->pai->esq;

            if (tio->cor == VERMELHO) {
                /* CASO 1 simétrico */
                z->pai->cor      = PRETO;
                tio->cor         = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;

            } else {
                if (z == z->pai->esq) {
                    /* CASO 2 simétrico */
                    z = z->pai;
                    rotacao_direita(t, z);
                }
                /* CASO 3 simétrico */
                z->pai->cor      = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacao_esquerda(t, z->pai->pai);
            }
        }
    }
    /* Prop. 2: raiz sempre preta */
    t->raiz->cor = PRETO;
}

/* Substitui a subárvore com raiz u pela subárvore com raiz v */
static void transplantar(ArvoreRB *t, No *u, No *v) {
    if (u->pai == t->nil)
        t->raiz = v;
    else if (u == u->pai->esq)
        u->pai->esq = v;
    else
        u->pai->dir = v;
    v->pai = u->pai;  /* v aponta para o pai de u (pode ser nil) */
}

/* Retorna o nó com menor valor na subárvore de x */
static No* minimo(ArvoreRB *t, No *x) {
    while (x->esq != t->nil)
        x = x->esq;
    return x;
}

static void remover_fixup(ArvoreRB *t, No *x) {
    while (x != t->raiz && x->cor == PRETO) {

        if (x == x->pai->esq) {
            /* x é filho ESQUERDO */
            No *w = x->pai->dir;  /* irmão de x */

            /* CASO 1: irmão VERMELHO ? rotaciona e converte */
            if (w->cor == VERMELHO) {
                w->cor       = PRETO;
                x->pai->cor  = VERMELHO;
                rotacao_esquerda(t, x->pai);
                w = x->pai->dir;  /* novo irmão após rotação */
            }

            /* CASO 2: irmão PRETO, ambos filhos pretos */
            if (w->esq->cor == PRETO && w->dir->cor == PRETO) {
                w->cor = VERMELHO;  /* transfere o duplo preto para cima */
                x = x->pai;

            } else {
                /* CASO 3: filho distante (dir) de w é PRETO */
                if (w->dir->cor == PRETO) {
                    w->esq->cor = PRETO;
                    w->cor      = VERMELHO;
                    rotacao_direita(t, w);
                    w = x->pai->dir;
                }
                /* CASO 4: filho distante (dir) de w é VERMELHO */
                w->cor       = x->pai->cor;
                x->pai->cor  = PRETO;
                w->dir->cor  = PRETO;
                rotacao_esquerda(t, x->pai);
                x = t->raiz;  /* encerra o loop */
            }

        } else {
            /* x é filho DIREITO (simétrico) */
            No *w = x->pai->esq;

            /* CASO 1 simétrico */
            if (w->cor == VERMELHO) {
                w->cor       = PRETO;
                x->pai->cor  = VERMELHO;
                rotacao_direita(t, x->pai);
                w = x->pai->esq;
            }

            /* CASO 2 simétrico */
            if (w->dir->cor == PRETO && w->esq->cor == PRETO) {
                w->cor = VERMELHO;
                x = x->pai;

            } else {
                /* CASO 3 simétrico */
                if (w->esq->cor == PRETO) {
                    w->dir->cor = PRETO;
                    w->cor      = VERMELHO;
                    rotacao_esquerda(t, w);
                    w = x->pai->esq;
                }
                /* CASO 4 simétrico */
                w->cor       = x->pai->cor;
                x->pai->cor  = PRETO;
                w->esq->cor  = PRETO;
                rotacao_direita(t, x->pai);
                x = t->raiz;
            }
        }
    }
    x->cor = PRETO;  /* garante que x (pode ser raiz) seja preto */
}


ArvoreRB* criar_arvore() {
    ArvoreRB *t = (ArvoreRB*)malloc(sizeof(ArvoreRB));

    t->nil        = (No*)malloc(sizeof(No));
    t->nil->cor   = PRETO;
    t->nil->esq   = t->nil;
    t->nil->dir   = t->nil;
    t->nil->pai   = t->nil;
    t->nil->valor = 0;

    t->raiz = t->nil;  /* árvore começa vazia */
    return t;
}

/* Inserção BST padrão seguida do ajuste de coloração */
void inserir(ArvoreRB *t, int valor) {
    No *z = criar_no(t, valor);
    No *y = t->nil;   /* pai do nó de inserção */
    No *x = t->raiz;

    /* Desce até encontrar a posição correta */
    while (x != t->nil) {
        y = x;
        if (z->valor < x->valor)
            x = x->esq;
        else
            x = x->dir;
    }

    z->pai = y;

    if (y == t->nil)
        t->raiz = z;          /* árvore estava vazia */
    else if (z->valor < y->valor)
        y->esq = z;
    else
        y->dir = z;

    /* Corrige as propriedades ARN violadas pela inserção */
    inserir_fixup(t, z);
}

/* Busca iterativa: O(log n) garantido pela balanceamento ARN */
No* buscar(ArvoreRB *t, int valor) {
    No *x = t->raiz;
    while (x != t->nil) {
        if (valor == x->valor)
            return x;           /* encontrado */
        else if (valor < x->valor)
            x = x->esq;
        else
            x = x->dir;
    }
    return NULL;  /* não encontrado */
}

/* Remove o nó com o valor dado, mantendo as propriedades ARN */
void remover(ArvoreRB *t, int valor) {
    No *z = buscar(t, valor);
    if (z == NULL) {
        printf("Valor %d nao encontrado na arvore.\n", valor);
        return;
    }

    No *y = z;              /* nó que será de fato desconectado */
    No *x;                  /* filho que substitui y */
    int cor_original = y->cor;

    if (z->esq == t->nil) {
        /* Caso A: sem filho esquerdo ? substitui por filho direito */
        x = z->dir;
        transplantar(t, z, z->dir);

    } else if (z->dir == t->nil) {
        /* Caso B: sem filho direito ? substitui por filho esquerdo */
        x = z->esq;
        transplantar(t, z, z->esq);

    } else {
        /* Caso C: dois filhos ? usa o sucessor (mínimo da subárvore dir) */
        y = minimo(t, z->dir);
        cor_original = y->cor;  /* cor do nó que será removido de lugar */
        x = y->dir;

        if (y->pai == z) {
            /* Sucessor é filho direto de z */
            x->pai = y;
        } else {
            transplantar(t, y, y->dir);
            y->dir     = z->dir;
            y->dir->pai = y;
        }

        transplantar(t, z, y);
        y->esq     = z->esq;
        y->esq->pai = y;
        y->cor     = z->cor;  /* y herda a cor de z */
    }

    free(z);

    /* Se a cor original era PRETA, pode ter criado duplo preto */
    if (cor_original == PRETO)
        remover_fixup(t, x);
}

/* exibe valor e cor (V=vermelho, P=preto) */
static void _em_ordem(ArvoreRB *t, No *x) {
    if (x != t->nil) {
        _em_ordem(t, x->esq);
        printf("%d(%c) ", x->valor, x->cor == VERMELHO ? 'V' : 'P');
        _em_ordem(t, x->dir);
    }
}

void imprimir_em_ordem(ArvoreRB *t) {
    printf("[ ");
    _em_ordem(t, t->raiz);
    printf("]\n");
}

/* Libera todos os nós recursivamente, depois o sentinela e a struct */
static void _liberar(ArvoreRB *t, No *x) {
    if (x != t->nil) {
        _liberar(t, x->esq);
        _liberar(t, x->dir);
        free(x);
    }
}

void liberar(ArvoreRB *t) {
    _liberar(t, t->raiz);
    free(t->nil);
    free(t);
}
