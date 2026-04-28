#include <stdio.h>
#include "dst.c"

int main() {
    NoDST* raiz = NULL;

    printf("==============================================\n");
    printf("  ARVORE DE BUSCA DIGITAL (DST) - %d BITS\n", W);
    printf("==============================================\n\n");

    // -------------------------------------------------------
    // TESTE 1: Insercao
    // -------------------------------------------------------
    printf("--- TESTE 1: Insercao ---\n");
    printf("Inserindo chaves: 5, 2, 8, 1, 7, 10, 3\n\n");

    raiz = inserir(raiz, 5);   // 00000101
    raiz = inserir(raiz, 2);   // 00000010
    raiz = inserir(raiz, 8);   // 00001000
    raiz = inserir(raiz, 1);   // 00000001
    raiz = inserir(raiz, 7);   // 00000111
    raiz = inserir(raiz, 10);  // 00001010
    raiz = inserir(raiz, 3);   // 00000011

    printf("\n");

    // -------------------------------------------------------
    // Visualizacao da arvore
    // -------------------------------------------------------
    printf("--- Estrutura da arvore (pre-ordem com indentacao) ---\n");
    pre_ordem(raiz);
    printf("\n");

    printf("--- Percurso em ordem ---\n");
    em_ordem(raiz);
    printf("\n");

    // -------------------------------------------------------
    // TESTE 2: Busca
    // -------------------------------------------------------
    printf("--- TESTE 2: Busca ---\n");

    int chaves_busca[] = {5, 7, 10, 15, 1};
    int i;
    int n_busca = sizeof(chaves_busca) / sizeof(chaves_busca[0]);

    for (i = 0; i < n_busca; i++) {
        NoDST* resultado = buscar(raiz, chaves_busca[i]);
        printf("Buscar %2d (", chaves_busca[i]);
        imprimir_bits(chaves_busca[i]);
        printf("): ");

        if (resultado != NULL) {
            printf("ENCONTRADA | Pai: ");
            if (resultado->p != NULL) {
                printf("%d\n", resultado->p->key);
            } else {
                printf("NULL (eh a raiz)\n");
            }
        } else {
            printf("NAO ENCONTRADA\n");
        }
    }
    printf("\n");

    // -------------------------------------------------------
    // TESTE 3: Demonstracao do caminho bit a bit
    // -------------------------------------------------------
    printf("--- TESTE 3: Caminho bit a bit ate uma chave ---\n");
    int chave_demo = 7; // 00000111
    printf("Rastreando caminho ate a chave %d (", chave_demo);
    imprimir_bits(chave_demo);
    printf("):\n");

    NoDST* atual = raiz;
    int nivel = 0;

    while (atual != NULL) {
        int bit = obter_bit(chave_demo, nivel);
        printf("  Nivel %d: no=%d, bit examinado=%d -> Child[%d]",
               nivel, atual->key, bit, bit);

        if (atual->key == chave_demo) {
            printf(" ** CHAVE ENCONTRADA **\n");
            break;
        }

        printf("\n");
        atual = atual->Child[bit];
        nivel++;
    }
    printf("\n");

    // -------------------------------------------------------
    // TESTE 4: Remocao
    // -------------------------------------------------------
    printf("--- TESTE 4: Remocao ---\n");

    // Caso 1: remover folha
    printf("Removendo 3 (folha)...\n");
    raiz = remover(raiz, 3);
    printf("Buscar 3: %s\n\n", buscar(raiz, 3) ? "ENCONTRADA" : "NAO ENCONTRADA");

    // Caso 2: remover no interno (tem filhos)
    printf("Removendo 2 (no interno)...\n");
    raiz = remover(raiz, 2);
    printf("Buscar 2: %s\n", buscar(raiz, 2) ? "ENCONTRADA" : "NAO ENCONTRADA");
    printf("Buscar 1: %s (filho de 2, deve continuar acessivel)\n\n",
           buscar(raiz, 1) ? "ENCONTRADA" : "NAO ENCONTRADA");

    // Caso 3: remover a raiz
    printf("Removendo 5 (raiz)...\n");
    raiz = remover(raiz, 5);
    printf("Buscar 5: %s\n\n", buscar(raiz, 5) ? "ENCONTRADA" : "NAO ENCONTRADA");

    // Caso 4: remover chave inexistente
    printf("Removendo 99 (inexistente)...\n");
    raiz = remover(raiz, 99);
    printf("\n");

    // Estado final
    printf("--- Arvore apos remocoes ---\n");
    printf("Estrutura (pre-ordem):\n");
    pre_ordem(raiz);
    printf("\nPercurso em ordem:\n");
    em_ordem(raiz);
    printf("\n");

    // Libera toda a memoria
    liberar(raiz);
    printf("Memoria liberada com sucesso.\n");

    return 0;
}
