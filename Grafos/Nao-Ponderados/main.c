#include <stdio.h>
#include "grafo.c"

int main() {

    Grafo* g = criar_grafo(5);

    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 0, 2);
    adicionar_aresta(g, 1, 3);
    adicionar_aresta(g, 2, 3);
    adicionar_aresta(g, 2, 4);

    // Mostra como o grafo ficou guardado na memoria
    printf("Estrutura do Grafo (Listas de Adjacencia) \n");
    imprimir_grafo(g);
    printf("\n");

    // Executa as duas buscas a partir do verrtice 0
    printf("Buscas (comecando no vertice 0) \n");
    bfs(g, 0);   // esperado: 0 1 2 3 4  (por largura)
    dfs(g, 0);   // esperado: 0 1 3 2 4  (por profundidade)

    // Sempre liberar a memoria ao final
    liberar_grafo(g);

    return 0;
}
