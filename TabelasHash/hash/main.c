#include <stdio.h>
#include "hash.c"

int main(void) {
    TabelaHash h;
    hash_init(&h);

    int chaves[] = {10, 22, 31, 4, 15, 28, 17, 88, 59};
    int n = sizeof(chaves) / sizeof(chaves[0]);

    printf("Inserindo %d elementos\n", n);
    int i;
    for (i = 0; i < n; i++)
        hash_insert(&h, chaves[i]);

    hash_print(&h);

    printf("\n Busca \n");
    int testes[] = {28, 99};
    for (i = 0; i < 2; i++) {
        No *r = hash_search(&h, testes[i]);
        printf("Busca %d: %s\n", testes[i], r ? "encontrado" : "nao encontrado");
    }

    printf("\n Remocao de 28 \n");
    hash_remove(&h, 28);
    hash_print(&h);

    hash_free(&h);
    return 0;
}
