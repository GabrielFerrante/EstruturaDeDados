#ifndef AVL_H
#define AVL_H

// Estrutura do nó da árvore AVL
typedef struct No {
    int valor;
    int altura;          // Altura do nó (folha = 0)
    struct No* esq;      // Filho esquerdo
    struct No* dir;      // Filho direito
} No;


No* criar_no(int valor);
int altura(No* no);
int fator_balanceamento(No* no);
int maior(int a, int b);
No* menor_valor(No* no);
No* rotacao_esquerda(No* no);
No* rotacao_direita(No* no);
No* rotacao_esquerda_direita(No* no);   
No* rotacao_direita_esquerda(No* no);   
No* inserir(No* raiz, int valor);
No* remover(No* raiz, int valor);
No* buscar(No* raiz, int valor);
void em_ordem(No* raiz);
void pre_ordem(No* raiz);
void pos_ordem(No* raiz);
void imprimir_arvore(No* raiz, int nivel, char direcao);
void liberar(No* raiz);

#endif
