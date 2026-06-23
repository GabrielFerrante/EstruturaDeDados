#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// CÓDIGO GERADO PELO CLAUDE
// REVISADO E VALIDADO POR GABRIEL S. FERRANTE
// USAR PARA SOMENTE CONTEÚDOS DIDÁTICOS

// Valor usado para representar "infinito": um vertice que ainda
// nao foi alcancado a partir da origem.
#define INFINITO INT_MAX

// ===============================================================
//  Criacao e manipulacao do grafo
// ===============================================================

// Cria um grafo com 'num_vertices' vertices e listas de adjacencia vazias.
Grafo* criar_grafo(int num_vertices) {
    Grafo* g = (Grafo*) malloc(sizeof(Grafo));
    g->num_vertices = num_vertices;

    // Aloca o vetor de listas de adjacencia (uma posicao por vertice)
    g->adj = (Aresta**) malloc(num_vertices * sizeof(Aresta*));

    // Inicializa cada lista como vazia (NULL = sem arestas)
    int i;
    for (i = 0; i < num_vertices; i++) {
        g->adj[i] = NULL;
    }
    return g;
}

// Adiciona uma aresta DIRECIONADA de 'origem' para 'destino' com o 'peso' dado.
// Para um grafo nao direcionado, basta chamar esta funcao duas vezes
// (origem->destino e destino->origem).
void adicionar_aresta(Grafo* g, int origem, int destino, int peso) {
    // Cria o novo no que representa a aresta
    Aresta* nova = (Aresta*) malloc(sizeof(Aresta));
    nova->destino = destino;
    nova->peso = peso;

    // Insere a nova aresta no inicio da lista de adjacencia da origem.
    // Inserir no inicio e O(1) e simples de entender.
    nova->prox = g->adj[origem];
    g->adj[origem] = nova;
}

// Imprime o grafo: para cada vertice, lista suas arestas e respectivos pesos.
void imprimir_grafo(Grafo* g) {
    int i;
    for (i = 0; i < g->num_vertices; i++) {
        printf("Vertice %d:", i);
        Aresta* atual = g->adj[i];
        while (atual != NULL) {
            printf(" -> %d (peso %d)", atual->destino, atual->peso);
            atual = atual->prox;
        }
        printf("\n");
    }
}

// Libera toda a memoria alocada pelo grafo (arestas, vetor e estrutura).
void liberar_grafo(Grafo* g) {
    int i;
    for (i = 0; i < g->num_vertices; i++) {
        Aresta* atual = g->adj[i];
        while (atual != NULL) {
            Aresta* temp = atual;   // guarda o no atual
            atual = atual->prox;    // avanca antes de liberar
            free(temp);             // libera o no guardado
        }
    }
    free(g->adj);
    free(g);
}

// ===============================================================
//  Funcao auxiliar para reconstruir o caminho
// ===============================================================

// Imprime recursivamente o caminho da origem ate 'v' usando o vetor
// de predecessores. O predecessor da origem e -1 (caso base).
static void imprimir_caminho(int predecessor[], int v) {
    if (predecessor[v] == -1) {
        // Chegamos na origem: ela nao tem predecessor
        printf("%d", v);
        return;
    }
    // Imprime primeiro tudo que vem antes de 'v' e depois 'v'
    imprimir_caminho(predecessor, predecessor[v]);
    printf(" -> %d", v);
}

// ===============================================================
//  Algoritmo de Dijkstra
//  - Funciona apenas com pesos NAO negativos.
//  - Encontra o caminho minimo da origem para todos os vertices.
//  - Estrategia: a cada passo "fecha" o vertice nao visitado de
//    menor distancia e relaxa suas arestas.
// ===============================================================
void dijkstra(Grafo* g, int origem) {
    int n = g->num_vertices;

    // Vetores auxiliares dimensionados pelo tamanho do grafo
    int* dist        = (int*) malloc(n * sizeof(int)); // menor distancia conhecida ate cada vertice
    int* predecessor = (int*) malloc(n * sizeof(int)); // vertice anterior no melhor caminho
    int* visitado    = (int*) malloc(n * sizeof(int)); // 1 se o vertice ja foi finalizado

    // Inicializacao: distancia infinita, sem predecessor e nao visitado
    int i;
    for (i = 0; i < n; i++) {
        dist[i] = INFINITO;
        predecessor[i] = -1;
        visitado[i] = 0;
    }
    dist[origem] = 0; // distancia da origem ate ela mesma e zero

    // Em um grafo com n vertices, fechamos no maximo n vertices
    int count;
    for (count = 0; count < n; count++) {

        // (1) Seleciona o vertice nao visitado de menor distancia.
        //     Aqui usamos busca linear (O(n)) por ser mais didatico.
        int u = -1;
        int menor = INFINITO;
        for (i = 0; i < n; i++) {
            if (!visitado[i] && dist[i] < menor) {
                menor = dist[i];
                u = i;
            }
        }

        // Se nao restou vertice alcancavel, podemos encerrar
        if (u == -1) {
            break;
        }

        // Marca o vertice escolhido como finalizado.
        // A distancia dele ja e definitiva (garantia do Dijkstra).
        visitado[u] = 1;

        // (2) Relaxa todas as arestas que saem de 'u'.
        Aresta* atual = g->adj[u];
        while (atual != NULL) {
            int v = atual->destino;
            int peso = atual->peso;

            // Se chegar em 'v' passando por 'u' for mais barato, atualiza.
            // A checagem dist[u] != INFINITO evita somar com "infinito".
            if (dist[u] != INFINITO && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                predecessor[v] = u;
            }
            atual = atual->prox;
        }
    }

    // Impressao dos resultados
    printf("\n=== Dijkstra (origem = %d) ===\n", origem);
    for (i = 0; i < n; i++) {
        printf("Vertice %d: ", i);
        if (dist[i] == INFINITO) {
            printf("inalcancavel\n");
        } else {
            printf("distancia = %d | caminho: ", dist[i]);
            imprimir_caminho(predecessor, i);
            printf("\n");
        }
    }

    free(dist);
    free(predecessor);
    free(visitado);
}

// ===============================================================
//  Algoritmo de Bellman-Ford
//  - Funciona com pesos negativos.
//  - Detecta a existencia de ciclos de peso negativo.
//  - Estrategia: relaxar TODAS as arestas (n-1) vezes e, em
//    seguida, testar se ainda e possivel relaxar (sinal de ciclo).
// ===============================================================
void bellman_ford(Grafo* g, int origem) {
    int n = g->num_vertices;

    int* dist        = (int*) malloc(n * sizeof(int));
    int* predecessor = (int*) malloc(n * sizeof(int));

    // Inicializacao identica a do Dijkstra
    int i;
    for (i = 0; i < n; i++) {
        dist[i] = INFINITO;
        predecessor[i] = -1;
    }
    dist[origem] = 0;

    // (1) Relaxa todas as arestas (n-1) vezes.
    //     Apos (n-1) rodadas, todas as distancias minimas ja convergiram
    //     (desde que nao exista ciclo negativo).
    int rodada;
    for (rodada = 0; rodada < n - 1; rodada++) {
        int u;
        for (u = 0; u < n; u++) {
            Aresta* atual = g->adj[u];
            while (atual != NULL) {
                int v = atual->destino;
                int peso = atual->peso;

                if (dist[u] != INFINITO && dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    predecessor[v] = u;
                }
                atual = atual->prox;
            }
        }
    }

    // (2) Verificacao de ciclo negativo:
    //     se na rodada extra ainda for possivel relaxar alguma aresta,
    //     entao existe um ciclo de peso negativo alcancavel.
    int tem_ciclo_negativo = 0;
    int u;
    for (u = 0; u < n; u++) {
        Aresta* atual = g->adj[u];
        while (atual != NULL) {
            int v = atual->destino;
            int peso = atual->peso;
            if (dist[u] != INFINITO && dist[u] + peso < dist[v]) {
                tem_ciclo_negativo = 1;
            }
            atual = atual->prox;
        }
    }

    // Impressao dos resultados
    printf("\n=== Bellman-Ford (origem = %d) ===\n", origem);
    if (tem_ciclo_negativo) {
        printf("O grafo contem um ciclo de peso negativo!\n");
        printf("Os caminhos minimos nao estao bem definidos.\n");
    } else {
        for (i = 0; i < n; i++) {
            printf("Vertice %d: ", i);
            if (dist[i] == INFINITO) {
                printf("inalcancavel\n");
            } else {
                printf("distancia = %d | caminho: ", dist[i]);
                imprimir_caminho(predecessor, i);
                printf("\n");
            }
        }
    }

    free(dist);
    free(predecessor);
}
