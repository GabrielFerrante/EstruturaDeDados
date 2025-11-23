#include <stdio.h>
#include "arvore_binaria.c"
#include <locale.h>
int main() {
	setlocale(LC_ALL, "portuguese");
    No* raiz = NULL;
    
    printf("=== ÁRVORE BINÁRIA SIMPLES ===\n\n");
    
    // Inserindo valores na árvore
    printf("Inserindo valores: 50, 30, 70, 20, 40, 60, 80\n");
    inserir(&raiz, 50);
    inserir(&raiz, 30);
    inserir(&raiz, 70);
    inserir(&raiz, 20);
    inserir(&raiz, 40);
    inserir(&raiz, 60);
    inserir(&raiz, 80);
    
    printf("\n");
    
    // Travessias
    printf("Travessia Pré-ordem: ");
    pre_ordem(raiz);
    printf("\n");
    
    printf("Travessia Em-ordem: ");
    em_ordem(raiz);
    printf("\n");
    
    printf("Travessia Pós-ordem: ");
    pos_ordem(raiz);
    printf("\n\n");
    
    // Busca
    int valor_busca = 40;
    No* resultado = buscar(raiz, valor_busca);
    if (resultado != NULL) {
        printf("Valor %d encontrado na árvore!\n", valor_busca);
    } else {
        printf("Valor %d não encontrado na árvore!\n", valor_busca);
    }
    
    valor_busca = 25;
    resultado = buscar(raiz, valor_busca);
    if (resultado != NULL) {
        printf("Valor %d encontrado na árvore!\n", valor_busca);
    } else {
        printf("Valor %d não encontrado na árvore!\n", valor_busca);
    }
    
    printf("\n");
    
    // Inserindo mais valores
    printf("Inserindo mais valores: 10, 35, 65\n");
    inserir(&raiz, 10);
    inserir(&raiz, 35);
    inserir(&raiz, 65);
    
    printf("Travessia Em-ordem atualizada: ");
    em_ordem(raiz);
    printf("\n\n");
    
    // Estrutura da árvore resultante:
    //         50
    //       /    \
    //     30      70
    //    /  \    /  \
    //  20   40  60   80
    //  /    /    \
    // 10   35    65
    
    printf("Estrutura da árvore:\n");
    printf("         50\n");
    printf("       /    \\\n");
    printf("     30      70\n");
    printf("    /  \\    /  \\\n");
    printf("  20   40  60   80\n");
    printf("  /    /    \\\n");
    printf(" 10   35    65\n\n");
    
    // Liberar memória
    liberar_arvore(raiz);
    printf("Árvore liberada da memória.\n");
    
    return 0;
}
