#ifndef GRAFO_H
#define GRAFO_H

// CÓDIGO GERADO PELO CLAUDE
// REVISADO E VALIDADO POR GABRIEL S. FERRANTE
// USAR PARA SOMENTE CONTEÚDOS DIDÁTICOS

// Estrutura que representa uma aresta dentro da lista de adjacencia.
// Cada vertice tem uma lista encadeada de arestas que saem dele.
typedef struct Aresta {
    int destino;          // vertice de destino da aresta
    int peso;             // peso (custo) da aresta
    struct Aresta* prox;  // ponteiro para a proxima aresta da mesma lista
} Aresta;

// Estrutura que representa o grafo ponderado direcionado.
// O grafo e armazenado como um vetor de listas de adjacencia.
typedef struct {
    int num_vertices;   // quantidade de vertices do grafo
    Aresta** adj;       // vetor de ponteiros: adj[v] e a lista de arestas que saem de v
} Grafo;

// Funcoes de manipulacao do grafo
Grafo* criar_grafo(int num_vertices);
void adicionar_aresta(Grafo* g, int origem, int destino, int peso);
void imprimir_grafo(Grafo* g);
void liberar_grafo(Grafo* g);

// Algoritmos de caminho minimo a partir de uma origem
void dijkstra(Grafo* g, int origem);
void bellman_ford(Grafo* g, int origem);

#endif
