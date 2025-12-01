#include <stdio.h>
#include "abb.c"
#include <locale.h>

int main() {
	setlocale(LC_ALL, "Portuguese");
    No* raiz = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(valores)/sizeof(valores[0]);
    
    // Inserção
    printf("Inserindo valores: ");
    int i = 0;
    for (i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        raiz = inserir(raiz, valores[i]);
    }
    printf("\n");
    
    // Travessia em ordem
    printf("Elementos em ordem: ");
    em_ordem(raiz);
    printf("\n");
    
    // Buscas
    printf("\nBuscas:\n");
    int busca[] = {40, 25, 70};
    i = 0;
    for (i = 0; i < 3; i++) {
        No* resultado = buscar(raiz, busca[i]);
        printf("Busca por %d: %s\n", 
               busca[i], 
               resultado ? "Encontrado" : "Não encontrado");
    }
    
    // Remoções
    printf("\nRemoções:\n");
    
    // Remover nó folha (20)
    printf("Removendo 20 (nó folha)...\n");
    raiz = remover(raiz, 20);
    printf("Elementos em ordem: ");
    em_ordem(raiz);
    printf("\n");
    
    // Remover nó com um filho (30)
    printf("Removendo 30 (nó com um filho)...\n");
    raiz = remover(raiz, 30);
    printf("Elementos em ordem: ");
    em_ordem(raiz);
    printf("\n");
    
    // Remover nó com dois filhos (50 - raiz)
    printf("Removendo 50 (nó com dois filhos)...\n");
    raiz = remover(raiz, 50);
    printf("Elementos em ordem: ");
    em_ordem(raiz);
    printf("\n");
    
    // Tentar remover elemento que não existe
    printf("Tentando remover 99 (não existe)...\n");
    raiz = remover(raiz, 99);
    printf("Elementos em ordem: ");
    em_ordem(raiz);
    printf("\n");
    
    // Adicionar mais elementos e testar outras remoções
    printf("\nAdicionando mais valores: 15, 45, 55, 75\n");
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 45);
    raiz = inserir(raiz, 55);
    raiz = inserir(raiz, 75);
    printf("Elementos em ordem: ");
    em_ordem(raiz);
    printf("\n");
    
    // Remover nó com dois filhos novamente
    printf("Removendo 70 (nó com dois filhos)...\n");
    raiz = remover(raiz, 70);
    printf("Elementos em ordem: ");
    em_ordem(raiz);
    printf("\n");
    
    liberar(raiz);
    printf("\nÁrvore liberada da memória.\n");
    
    return 0;
}
