#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

// CÓDIGO GERADO PELO CLAUDE
// REVISADO E VALIDADO POR GABRIEL S. FERRANTE
// USAR PARA SOMENTE CONTEÚDOS DIDÁTICOS


static No* criar_no(int vertice) {
    No* novo = (No*) malloc(sizeof(No));
    novo->vertice = vertice;
    novo->proximo = NULL;
    return novo;
}

// Insere 'vertice' no FINAL da lista apontada por '*lista'.
// Inserir no fim mantem a ordem de insercao das arestas, o que deixa
// a saida da BFS/DFS mais previsivel e facil de acompanhar.
static void inserir_no_fim(No** lista, int vertice) {
    No* novo = criar_no(vertice);

    if (*lista == NULL) {     
        *lista = novo;
        return;
    }

    No* atual = *lista;       
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }
    atual->proximo = novo;    
}


Grafo* criar_grafo(int num_vertices) {
    Grafo* g = (Grafo*) malloc(sizeof(Grafo));
    g->num_vertices = num_vertices;

    
    g->listas_adj = (No**) malloc(num_vertices * sizeof(No*));

    
    int i;
    for (i = 0; i < num_vertices; i++) {
        g->listas_adj[i] = NULL;
    }
    return g;
}

void adicionar_aresta(Grafo* g, int origem, int destino) {
   
    inserir_no_fim(&g->listas_adj[origem], destino); // origem  -> destino
    inserir_no_fim(&g->listas_adj[destino], origem); // destino -> origem

    // OBS: para um grafo DIRECIONADO, bastaria manter so a primeira linha.
}

void imprimir_grafo(Grafo* g) {
    int i;
    for (i = 0; i < g->num_vertices; i++) {
        printf("Vertice %d:", i);

        No* atual = g->listas_adj[i];
        while (atual != NULL) {
            printf(" -> %d", atual->vertice);
            atual = atual->proximo;
        }
        printf("\n");
    }
}

void bfs(Grafo* g, int inicio) {
    
    //vetor de visitados
    int* visitado = (int*) calloc(g->num_vertices, sizeof(int));


    int* fila = (int*) malloc(g->num_vertices * sizeof(int));
    int frente = 0, tras = 0;   // frente = remove; tras = insere

    
    visitado[inicio] = 1;
    fila[tras++] = inicio;

    printf("BFS a partir do vertice %d: ", inicio);

    
    while (frente < tras) {
        int atual = fila[frente++];   // retira o primeiro da fila
        printf("%d ", atual);

        
        No* vizinho = g->listas_adj[atual];
        while (vizinho != NULL) {
            // Se ainda nao foi visitado: marca e coloca na fila
            if (!visitado[vizinho->vertice]) {
                visitado[vizinho->vertice] = 1;
                fila[tras++] = vizinho->vertice;
            }
            vizinho = vizinho->proximo;
        }
    }
    printf("\n");

    free(visitado);
    free(fila);
}



static void dfs_recursivo(Grafo* g, int vertice, int* visitado) {
    
    visitado[vertice] = 1;
    printf("%d ", vertice);

    
    No* vizinho = g->listas_adj[vertice];
    while (vizinho != NULL) {
        if (!visitado[vizinho->vertice]) {
            dfs_recursivo(g, vizinho->vertice, visitado);
        }
        vizinho = vizinho->proximo;
    }
}

void dfs(Grafo* g, int inicio) {
    int* visitado = (int*) calloc(g->num_vertices, sizeof(int));

    printf("DFS a partir do vertice %d: ", inicio);
    dfs_recursivo(g, inicio, visitado);
    printf("\n");

    free(visitado);
}

void liberar_grafo(Grafo* g) {
    int i;
    
    for (i = 0; i < g->num_vertices; i++) {
        No* atual = g->listas_adj[i];
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g->listas_adj);  // libera o vetor de listas
    free(g);              // libera a estrutura do grafo
}
