#include <stdio.h>
#include "rb.c"

int main() {
    ArvoreRB *t = criar_arvore();

    printf("=== INSERCOES ===\n");
    int valores[] = {10, 20, 30, 15, 25, 5, 1, 18};
    int n = sizeof(valores) / sizeof(valores[0]);
	int i = 0;
    for (i = 0; i < n; i++) {
        inserir(t, valores[i]);
        printf("Inserido %2d: ", valores[i]);
        imprimir_em_ordem(t);
    }

    printf("\n=== BUSCA ===\n");
    int alvos[] = {15, 18, 99};
    i = 0;
    for (i = 0; i < 3; i++) {
        No *res = buscar(t, alvos[i]);
        printf("Buscar %2d: %s\n", alvos[i], res ? "Encontrado" : "Nao encontrado");
    }

    printf("\n=== REMOCOES ===\n");

    remover(t, 1);   /* folha preta ? ativa fixup */
    printf("Removido  1: ");
    imprimir_em_ordem(t);

    remover(t, 30);  /* nó com 1 filho */
    printf("Removido 30: ");
    imprimir_em_ordem(t);

    remover(t, 20);  /* nó com 2 filhos ? usa sucessor (25) */
    printf("Removido 20: ");
    imprimir_em_ordem(t);

    remover(t, 10);  /* raiz */
    printf("Removido 10: ");
    imprimir_em_ordem(t);

    remover(t, 99);  /* valor inexistente */

    liberar(t);
    return 0;
}
