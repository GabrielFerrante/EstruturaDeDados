#include <stdio.h>
#include "avl.c"

// Função auxiliar para imprimir separadores
void separador(const char* titulo) {
    printf("\n========================================\n");
    printf("  %s\n", titulo);
    printf("========================================\n");
}

int main() {
    No* raiz = NULL;
    No* resultado;

    separador("TESTE 1: Insercao SEM rotacao");

    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);

    printf("\nArvore apos insercoes (30, 20, 40):\n");
    imprimir_arvore(raiz, 0, 'R');
    printf("Em ordem: ");
    em_ordem(raiz);
    printf("\n");

    separador("TESTE 2: Caso LL (Rotacao Direita)");

    // Recomeça com árvore limpa
    liberar(raiz);
    raiz = NULL;

    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    printf("-> Inserindo 10 (vai causar caso LL no no 30):\n");
    raiz = inserir(raiz, 10);

    printf("\nArvore balanceada:\n");
    imprimir_arvore(raiz, 0, 'R');

    
    separador("TESTE 3: Caso RR (Rotacao Esquerda)");

    liberar(raiz);
    raiz = NULL;

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    printf("-> Inserindo 30 (vai causar caso RR no no 10):\n");
    raiz = inserir(raiz, 30);

    printf("\nArvore balanceada:\n");
    imprimir_arvore(raiz, 0, 'R');

    
    separador("TESTE 4: Caso LR (Rotacao Esquerda-Direita)");

    liberar(raiz);
    raiz = NULL;

    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 10);
    printf("-> Inserindo 20 (vai causar caso LR no no 30):\n");
    raiz = inserir(raiz, 20);

    printf("\nArvore balanceada:\n");
    imprimir_arvore(raiz, 0, 'R');

    
    separador("TESTE 5: Caso RL (Rotacao Direita-Esquerda)");

    liberar(raiz);
    raiz = NULL;

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 30);
    printf("-> Inserindo 20 (vai causar caso RL no no 10):\n");
    raiz = inserir(raiz, 20);

    printf("\nArvore balanceada:\n");
    imprimir_arvore(raiz, 0, 'R');

    
    separador("TESTE 6: Busca");

    liberar(raiz);
    raiz = NULL;

    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);

    printf("\nArvore:\n");
    imprimir_arvore(raiz, 0, 'R');

    // Busca por valor existente
    resultado = buscar(raiz, 40);
    printf("\nBusca por 40: %s\n", resultado ? "ENCONTRADO" : "NAO ENCONTRADO");

    // Busca por valor inexistente
    resultado = buscar(raiz, 99);
    printf("Busca por 99: %s\n", resultado ? "ENCONTRADO" : "NAO ENCONTRADO");

    
    separador("TESTE 7: Remocao SEM rotacao");

    printf("\nArvore antes da remocao:\n");
    imprimir_arvore(raiz, 0, 'R');

    printf("\n-> Removendo folha 40:\n");
    raiz = remover(raiz, 40);

    printf("\nArvore apos remocao:\n");
    imprimir_arvore(raiz, 0, 'R');

    
    separador("TESTE 8: Remocao COM rotacao");

    liberar(raiz);
    raiz = NULL;

    // Monta uma árvore específica
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);
    raiz = inserir(raiz, 10);

    printf("\nArvore antes da remocao:\n");
    imprimir_arvore(raiz, 0, 'R');

    // Removendo 60 e 80 vai desbalancear o lado direito
    printf("\n-> Removendo 60:\n");
    raiz = remover(raiz, 60);
    printf("\n-> Removendo 80 (vai causar rotacao):\n");
    raiz = remover(raiz, 80);

    printf("\nArvore apos remocoes (rebalanceada):\n");
    imprimir_arvore(raiz, 0, 'R');

   
    separador("TESTE 9: Remocao de no com dois filhos");

    liberar(raiz);
    raiz = NULL;

    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 25);
    raiz = inserir(raiz, 75);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 90);

    printf("\nArvore antes:\n");
    imprimir_arvore(raiz, 0, 'R');

    printf("\n-> Removendo raiz 50 (tem dois filhos):\n");
    raiz = remover(raiz, 50);

    printf("\nArvore apos remocao da raiz:\n");
    imprimir_arvore(raiz, 0, 'R');
    printf("Em ordem: ");
    em_ordem(raiz);
    printf("\n");

    
    separador("TESTE 10: Valor duplicado");

    printf("\n-> Tentando inserir 25 novamente:\n");
    raiz = inserir(raiz, 25);

    
    separador("TESTE 11: Insercao sequencial (1..15)");

    liberar(raiz);
    raiz = NULL;

    int i;
    for (i = 1; i <= 15; i++) {
        raiz = inserir(raiz, i);
    }

    printf("\nArvore final (sequencia 1-15, perfeitamente balanceada):\n");
    imprimir_arvore(raiz, 0, 'R');

    printf("\nEm ordem: ");
    em_ordem(raiz);
    printf("\nPre ordem: ");
    pre_ordem(raiz);
    printf("\nPos ordem: ");
    pos_ordem(raiz);
    printf("\n");

    printf("\nAltura da arvore: %d (esperado ~3 para 15 nos)\n", altura(raiz));

    // Libera toda a memória
    liberar(raiz);
    raiz = NULL;

    printf("\nMemoria liberada com sucesso!\n");

    return 0;
}
