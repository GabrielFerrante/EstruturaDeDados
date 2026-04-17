#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


int maior(int a, int b) {
    return (a > b) ? a : b;
}


int altura(No* no) {
    if (no == NULL)
        return -1;
    return no->altura;
}


int fator_balanceamento(No* no) {
    if (no == NULL)
        return 0;
    return altura(no->esq) - altura(no->dir);
}

No* criar_no(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: falha ao alocar memoria!\n");
        return NULL;
    }
    novo->valor = valor;
    novo->altura = 0;   
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}


No* menor_valor(No* no) {
    No* atual = no;
    while (atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

No* rotacao_esquerda(No* no) {

    No* nova_raiz = no->dir;       
    No* sub_esq = nova_raiz->esq;  

    // Realiza a rotação
    nova_raiz->esq = no;           
    no->dir = sub_esq;            

  
    no->altura = 1 + maior(altura(no->esq), altura(no->dir));
    nova_raiz->altura = 1 + maior(altura(nova_raiz->esq), altura(nova_raiz->dir));

    return nova_raiz;  
}


No* rotacao_direita(No* no) {

    No* nova_raiz = no->esq;        
    No* sub_dir = nova_raiz->dir;   

    // Realiza a rotação
    nova_raiz->dir = no;            
    no->esq = sub_dir;              

  
    no->altura = 1 + maior(altura(no->esq), altura(no->dir));
    nova_raiz->altura = 1 + maior(altura(nova_raiz->esq), altura(nova_raiz->dir));

    return nova_raiz;  
}

No* rotacao_esquerda_direita(No* no) {
    
    no->esq = rotacao_esquerda(no->esq);
    
    return rotacao_direita(no);
}

//
No* rotacao_direita_esquerda(No* no) {
    
    no->dir = rotacao_direita(no->dir);
    
    return rotacao_esquerda(no);
}


No* balancear(No* no) {
    int fb = fator_balanceamento(no);

    
    if (fb > 1) {
       
        if (fator_balanceamento(no->esq) >= 0) {
            printf("  [Rotacao simples a direita no no %d]\n", no->valor);
            return rotacao_direita(no);
        }
       
        else {
            printf("  [Rotacao dupla esquerda-direita no no %d]\n", no->valor);
            return rotacao_esquerda_direita(no);
        }
    }

    
    if (fb < -1) {
        
        if (fator_balanceamento(no->dir) <= 0) {
            printf("  [Rotacao simples a esquerda no no %d]\n", no->valor);
            return rotacao_esquerda(no);
        }
        
        else {
            printf("  [Rotacao dupla direita-esquerda no no %d]\n", no->valor);
            return rotacao_direita_esquerda(no);
        }
    }

    return no;
}


No* buscar(No* raiz, int valor) {
    
    if (raiz == NULL) {
        return NULL;
    }

   
    if (valor == raiz->valor) {
        return raiz;
    }

   
    if (valor < raiz->valor) {
        return buscar(raiz->esq, valor);
    }

    
    return buscar(raiz->dir, valor);
}

No* inserir(No* raiz, int valor) {
    
    if (raiz == NULL) {
        printf("Inserindo valor %d\n", valor);
        return criar_no(valor);
    }

   
    if (valor < raiz->valor) {
        raiz->esq = inserir(raiz->esq, valor);
    }
    
    else if (valor > raiz->valor) {
        raiz->dir = inserir(raiz->dir, valor);
    }
   
    else {
        printf("Valor %d ja existe na arvore. Ignorando.\n", valor);
        return raiz;
    }

    
    raiz->altura = 1 + maior(altura(raiz->esq), altura(raiz->dir));

    
    raiz = balancear(raiz);

    return raiz;
}

//
No* remover(No* raiz, int valor) {
   
    if (raiz == NULL) {
        printf("Valor %d nao encontrado na arvore.\n", valor);
        return NULL;
    }

    
    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    }
    else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    }
   
    else {
        printf("Removendo valor %d\n", valor);

        // Caso 1: Nó folha (sem filhos)
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }

        // Caso 2a: Apenas filho direito
        if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        }

        // Caso 2b: Apenas filho esquerdo
        if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // Caso 3: Dois filhos
        // Encontra o sucessor in-order (menor da subárvore direita)
        No* sucessor = menor_valor(raiz->dir);
        printf("  Substituindo %d pelo sucessor %d\n", raiz->valor, sucessor->valor);

        // Copia o valor do sucessor para o nó atual
        raiz->valor = sucessor->valor;

        // Remove o sucessor da subárvore direita
        raiz->dir = remover(raiz->dir, sucessor->valor);
    }

    // --- Atualiza a altura do nó atual ---
    raiz->altura = 1 + maior(altura(raiz->esq), altura(raiz->dir));

    // --- Verifica e corrige o balanceamento ---
    raiz = balancear(raiz);

    return raiz;
}


void em_ordem(No* raiz) {
    if (raiz != NULL) {
        em_ordem(raiz->esq);
        printf("%d ", raiz->valor);
        em_ordem(raiz->dir);
    }
}


void pre_ordem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        pre_ordem(raiz->esq);
        pre_ordem(raiz->dir);
    }
}


void pos_ordem(No* raiz) {
    if (raiz != NULL) {
        pos_ordem(raiz->esq);
        pos_ordem(raiz->dir);
        printf("%d ", raiz->valor);
    }
}

// FEITO COM O CLAUDE, PARA VISUALIZAÇÃO !!
// Imprime a árvore de forma visual (rotacionada 90° para a esquerda)
// 'nivel' controla a indentação, 'direcao' indica se é raiz/esq/dir
void imprimir_arvore(No* raiz, int nivel, char direcao) {
    if (raiz == NULL)
        return;

    // Imprime a subárvore direita primeiro (aparece em cima)
    imprimir_arvore(raiz->dir, nivel + 1, '/');

    // Indentação proporcional ao nível
    int i;
    for (i = 0; i < nivel; i++)
        printf("        ");

    // Imprime o nó com seu FB (fator de balanceamento)
    printf("%c--[%d](FB=%d)\n", direcao, raiz->valor, fator_balanceamento(raiz));

    // Imprime a subárvore esquerda (aparece embaixo)
    imprimir_arvore(raiz->esq, nivel + 1, '\\');
}

// Libera toda a memória da árvore (pós-ordem)
void liberar(No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz);
    }
}
