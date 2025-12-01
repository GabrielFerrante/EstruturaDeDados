#include "abb.h"
#include <stdlib.h>
#include <stdio.h>

No* criar_no(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No* inserir(No* raiz, int valor) {
    if (raiz == NULL) return criar_no(valor);
    
    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);
    
    return raiz;
}

No* buscar(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor)
        return raiz;
    
    if (valor < raiz->valor)
        return buscar(raiz->esq, valor);
    else
        return buscar(raiz->dir, valor);
}

// Encontra o menor valor (mais à esquerda)
No* menor_valor(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual;
}
// Encontra o maior valor (mais à direita) da subárvore esquerda
No* maior_valor(No* raiz) {
    No* atual = raiz;
    while (atual && atual->dir != NULL)
        atual = atual->dir;
    return atual;
}
No* remover(No* raiz, int valor) {
    if (raiz == NULL) return raiz;
    
    // Buscar o nó a ser removido
    if (valor < raiz->valor)
        raiz->esq = remover(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = remover(raiz->dir, valor);
    else {
        // Nó encontrado
        
        // Caso 1: Nó com apenas um filho ou nenhum filho
        if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        
        // Caso 2: Nó com dois filhos
        // Encontrar o sucessor in-order (menor na subárvore direita)
        // Note que usar o predecessor in-order também da certo, fica a sua escolha
        No* temp = menor_valor(raiz->dir);
        
        // Copiar o valor do sucessor para este nó
        raiz->valor = temp->valor;
        
        // Remover o sucessor
        raiz->dir = remover(raiz->dir, temp->valor);
        
        //	(predecessor in-order):
		//No* temp = maior_valor(raiz->esq);
		//raiz->valor = temp->valor;
		//raiz->esq = remover(raiz->esq, temp->valor);
    }
    return raiz;
}

void em_ordem(No* raiz) {
    if (raiz != NULL) {
        em_ordem(raiz->esq);
        printf("%d ", raiz->valor);
        em_ordem(raiz->dir);
    }
}

void liberar(No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz);
    }
}
