#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

void hash_init(TabelaHash *h) {
    int i;
    for (i = 0; i < TAMANHO; i++)
        h->tabela[i] = NULL;
    h->total = 0;
}

/* divisao pelo tamanho da tabela (primo) */
int hash_func(int chave) {
    return ((chave % TAMANHO) + TAMANHO) % TAMANHO;  /* trata negativos */
}

void hash_insert(TabelaHash *h, int chave) {
    if (hash_search(h, chave)) {
        printf("Chave %d ja existe.\n", chave);
        return;
    }

    int pos = hash_func(chave);
    No *novo = (No *)malloc(sizeof(No));
    novo->chave   = chave;
    novo->proximo = h->tabela[pos]; /* insere na cabeca da lista */
    h->tabela[pos] = novo;
    h->total++;
}

No *hash_search(TabelaHash *h, int chave) {
    int pos = hash_func(chave);
    No *cur = h->tabela[pos];
    while (cur) {
        if (cur->chave == chave) return cur;
        cur = cur->proximo;
    }
    return NULL;
}

int hash_remove(TabelaHash *h, int chave) {
    int pos = hash_func(chave);
    No *cur  = h->tabela[pos];
    No *prev = NULL;

    while (cur) {
        if (cur->chave == chave) {
            if (prev) prev->proximo = cur->proximo;
            else       h->tabela[pos] = cur->proximo;
            free(cur);
            h->total--;
            return 1;
        }
        prev = cur;
        cur  = cur->proximo;
    }
    return 0; /* nao encontrado */
}

void hash_print(TabelaHash *h) {
    int i;
    printf("\n Tabela Hash Convencional (tamanho=%d)\n", TAMANHO);
    for (i = 0; i < TAMANHO; i++) {
        printf("[%2d] -> ", i);
        No *cur = h->tabela[i];
        while (cur) {
            printf("%d -> ", cur->chave);
            cur = cur->proximo;
        }
        printf("NULL\n");
    }
    printf("Total de elementos: %d\n", h->total);
}

void hash_free(TabelaHash *h) {
    int i;
    for (i = 0; i < TAMANHO; i++) {
        No *cur = h->tabela[i];
        while (cur) {
            No *temp = cur;
            cur = cur->proximo;
            free(temp);
        }
        h->tabela[i] = NULL;
    }
    h->total = 0;
}
