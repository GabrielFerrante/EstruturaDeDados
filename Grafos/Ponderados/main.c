#include <stdio.h>
#include "grafo.c"

// CÓDIGO GERADO PELO CLAUDE
// REVISADO E VALIDADO POR GABRIEL S. FERRANTE
// USAR PARA SOMENTE CONTEÚDOS DIDÁTICOS

int main() {

    //  EXEMPLO 1: grafo com pesos POSITIVOS
    //  Dijkstra e Bellman-Ford devem produzir o MESMO resultado.
    //
    //        (10)        (1)
    //    0 -------> 1 -------> 2
    //    |        ^ |        ^ |
    //  (5)|    (3)/  |(2)  (6)/  |(4)
    //    v      /   v      /   v
    //    4 <---     ...    3 <---
    //
    //  Arestas (direcionadas):
    //    0->1 (10), 0->4 (5)
    //    1->2 (1),  1->4 (2)
    //    4->1 (3),  4->2 (9), 4->3 (2)
    //    2->3 (4)
    //    3->2 (6),  3->0 (7)

    printf("############# EXEMPLO 1: pesos positivos #############\n");

    Grafo* g1 = criar_grafo(5);
    adicionar_aresta(g1, 0, 1, 10);
    adicionar_aresta(g1, 0, 4, 5);
    adicionar_aresta(g1, 1, 2, 1);
    adicionar_aresta(g1, 1, 4, 2);
    adicionar_aresta(g1, 4, 1, 3);
    adicionar_aresta(g1, 4, 2, 9);
    adicionar_aresta(g1, 4, 3, 2);
    adicionar_aresta(g1, 2, 3, 4);
    adicionar_aresta(g1, 3, 2, 6);
    adicionar_aresta(g1, 3, 0, 7);

    printf("\nEstrutura do grafo:\n");
    imprimir_grafo(g1);

    // Ambos a partir do vertice 0
    dijkstra(g1, 0);
    bellman_ford(g1, 0);

    liberar_grafo(g1);

    // ===========================================================
    //  EXEMPLO 2: grafo com pesos NEGATIVOS (sem ciclo negativo)
    //  Aqui o Dijkstra NAO e confiavel (pode dar resultado errado),
    //  enquanto o Bellman-Ford lida corretamente com os negativos.
    //
    //  Arestas (direcionadas):
    //    0->1 (6), 0->2 (7)
    //    1->2 (8), 1->3 (5), 1->4 (-4)
    //    2->3 (-3), 2->4 (9)
    //    3->1 (-2)
    //    4->0 (2), 4->3 (7)
    // ===========================================================
    printf("\n\n########## EXEMPLO 2: pesos negativos (sem ciclo) ##########\n");

    Grafo* g2 = criar_grafo(5);
    adicionar_aresta(g2, 0, 1, 6);
    adicionar_aresta(g2, 0, 2, 7);
    adicionar_aresta(g2, 1, 2, 8);
    adicionar_aresta(g2, 1, 3, 5);
    adicionar_aresta(g2, 1, 4, -4);
    adicionar_aresta(g2, 2, 3, -3);
    adicionar_aresta(g2, 2, 4, 9);
    adicionar_aresta(g2, 3, 1, -2);
    adicionar_aresta(g2, 4, 0, 2);
    adicionar_aresta(g2, 4, 3, 7);

    printf("\nEstrutura do grafo:\n");
    imprimir_grafo(g2);

    // Rodamos Dijkstra so para mostrar que ele pode falhar com negativos
    dijkstra(g2, 0);
    // Bellman-Ford da o resultado correto
    bellman_ford(g2, 0);

    liberar_grafo(g2);

    // ===========================================================
    //  EXEMPLO 3: grafo COM ciclo de peso negativo
    //  O ciclo 1 -> 2 -> 3 -> 1 soma (-1) + (-1) + (-1) = -3 < 0.
    //  O Bellman-Ford deve DETECTAR esse ciclo negativo.
    //
    //  Arestas (direcionadas):
    //    0->1 (1)
    //    1->2 (-1)
    //    2->3 (-1)
    //    3->1 (-1)
    // ===========================================================
    printf("\n\n########## EXEMPLO 3: com ciclo negativo ##########\n");

    Grafo* g3 = criar_grafo(4);
    adicionar_aresta(g3, 0, 1, 1);
    adicionar_aresta(g3, 1, 2, -1);
    adicionar_aresta(g3, 2, 3, -1);
    adicionar_aresta(g3, 3, 1, -1);

    printf("\nEstrutura do grafo:\n");
    imprimir_grafo(g3);

    // So o Bellman-Ford consegue detectar o ciclo negativo
    bellman_ford(g3, 0);

    liberar_grafo(g3);

    return 0;
}
