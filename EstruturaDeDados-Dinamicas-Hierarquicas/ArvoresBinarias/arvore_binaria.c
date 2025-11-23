#include "arvore_binaria.h"
#include <stdio.h>
#include <stdlib.h>

No* criar_no(int valor) {
    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }
    novo_no->valor = valor;
    novo_no->esquerda = NULL;
    novo_no->direita = NULL;
    return novo_no;
}

void inserir(No** raiz, int valor) {
    if (*raiz == NULL) {
        *raiz = criar_no(valor);
        return;
    }
    
    if (valor < (*raiz)->valor) {
        inserir(&(*raiz)->esquerda, valor);
    } else if (valor > (*raiz)->valor) {
        inserir(&(*raiz)->direita, valor);
    }
    // Se o valor for igual, não faz nada (não permite duplicatas)
}

void pre_ordem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        pre_ordem(raiz->esquerda);
        pre_ordem(raiz->direita);
    }
}

void em_ordem(No* raiz) {
    if (raiz != NULL) {
        em_ordem(raiz->esquerda);
        printf("%d ", raiz->valor);
        em_ordem(raiz->direita);
    }
}

void pos_ordem(No* raiz) {
    if (raiz != NULL) {
        pos_ordem(raiz->esquerda);
        pos_ordem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

No* buscar(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }
    
    if (valor < raiz->valor) {
        return buscar(raiz->esquerda, valor);
    } else {
        return buscar(raiz->direita, valor);
    }
}

void liberar_arvore(No* raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esquerda);
        liberar_arvore(raiz->direita);
        free(raiz);
    }
}
