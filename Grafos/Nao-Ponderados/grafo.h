#ifndef GRAFO_H
#define GRAFO_H


typedef struct No {
    int vertice;         
    struct No* proximo;   
} No;

// Estrutura do grafo
typedef struct {
    int num_vertices;     
    No** listas_adj;      
} Grafo;


Grafo* criar_grafo(int num_vertices);
void adicionar_aresta(Grafo* g, int origem, int destino);
void imprimir_grafo(Grafo* g);
void bfs(Grafo* g, int inicio);
void dfs(Grafo* g, int inicio);
void liberar_grafo(Grafo* g);

#endif
