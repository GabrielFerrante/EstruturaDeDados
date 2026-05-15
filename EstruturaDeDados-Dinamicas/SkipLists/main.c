#include <stdio.h>
#include "skip_list.c"

/*  imprime resultado de busca */
static void testar_busca(SkipList *sl, int valor) {
    No *resultado = sl_buscar(sl, valor);
    if (resultado) {
        printf("  Busca(%d): ENCONTRADO\n", valor);
    } else {
        printf("  Busca(%d): NAO ENCONTRADO\n", valor);
    }
}

/* imprime resultado de remoção */
static void testar_remocao(SkipList *sl, int valor) {
    int ok = sl_remover(sl, valor);
    if (ok) {
        printf("  Remover(%d): OK\n", valor);
    } else {
        printf("  Remover(%d): VALOR NAO ENCONTRADO\n", valor);
    }
}

int main(void) {

    SkipList sl;
    sl_inicializar(&sl);


    printf(" CENARIO 1: Insercoes basicas\n");

    int valores[] = {30, 10, 50, 20, 40, 60, 5, 70};
    int n = sizeof(valores) / sizeof(valores[0]);
    int i;

    printf("Inserindo: ");
    for (i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        sl_inserir(&sl, valores[i]);
    }
    printf("\n");

    sl_imprimir(&sl);
    sl_imprimir_nivel_base(&sl);


    printf(" CENARIO 2: Busca\n");

    testar_busca(&sl, 20);  /* deve encontrar */
    testar_busca(&sl, 50);  /* deve encontrar */
    testar_busca(&sl, 99);  /* deve NÃO encontrar */
    testar_busca(&sl,  1);  /* deve NÃO encontrar */


    printf(" CENARIO 3: Remocao\n");
  
    testar_remocao(&sl, 10);  /* remoção de elemento existente */
    testar_remocao(&sl, 99);  /* tentativa com elemento inexistente */
    testar_remocao(&sl, 70);  /* remoção do último elemento */
    testar_remocao(&sl,  5);  /* remoção do primeiro elemento */

    printf("\nApos remocoes:\n");
    sl_imprimir(&sl);
    sl_imprimir_nivel_base(&sl);


    printf(" CENARIO 4: Duplicatas\n");
   
    printf("Tentando inserir 30 (ja existe):\n");
    sl_inserir(&sl, 30);
    sl_imprimir_nivel_base(&sl);


    printf(" CENARIO 5: Esvaziamento total\n");
    int restantes[] = {20, 30, 40, 50, 60};
    for (i = 0; i < 5; i++) {
        testar_remocao(&sl, restantes[i]);
    }
    printf("\nApos esvaziar:\n");
    sl_imprimir(&sl);



    printf(" CENARIO 6: Reinsercao apos esvaziar\n");
 
    sl_inserir(&sl, 100);
    sl_inserir(&sl,  42);
    sl_inserir(&sl,  77);
    sl_imprimir(&sl);
    sl_imprimir_nivel_base(&sl);

    sl_liberar(&sl);
    printf("Memoria liberada com sucesso.\n");

    return 0;
}
