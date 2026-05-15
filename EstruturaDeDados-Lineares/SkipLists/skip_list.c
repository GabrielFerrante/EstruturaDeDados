#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "skip_list.h"


static No *criar_no(int valor, int altura) {
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) {
        fprintf(stderr, "Erro: falha ao alocar no.\n");
        exit(EXIT_FAILURE);
    }

    novo->valor  = valor;
    novo->frente = (No **)calloc(altura, sizeof(No *));
    if (!novo->frente) {
        fprintf(stderr, "Erro: falha ao alocar ponteiros do no.\n");
        free(novo);
        exit(EXIT_FAILURE);
    }

    return novo;
}


void sl_inicializar(SkipList *sl) {
    srand((unsigned int)time(NULL));

    /* O nó cabeça precisa de ponteiros em TODOS os níveis possíveis, pois ele é o ponto de entrada de qualquer busca */
    sl->cabeca       = criar_no(0, MAX_NIVEL);
    sl->nivel_atual  = 0;
    sl->tamanho      = 0;
}


int sl_nivel_aleatorio(void) {
    int nivel = 1;
    while ((double)rand() / RAND_MAX < PROBABILIDADE && nivel < MAX_NIVEL) {
        nivel++;
    }
    return nivel;
}


void sl_inserir(SkipList *sl, int valor) {
    /* atualizar[i] = último nó no nível i cujo próximo
       deve apontar para o novo nó após a inserção */
    No *atualizar[MAX_NIVEL];
    No *atual = sl->cabeca;

    /* Fase 1: encontrar predecessores em cada nível  */
    int i;
    for (i = sl->nivel_atual - 1; i >= 0; i--) {
        /* Avança enquanto o próximo existe e é menor que o valor */
        while (atual->frente[i] && atual->frente[i]->valor < valor) {
            atual = atual->frente[i];
        }
        atualizar[i] = atual; /* predecessor no nível i */
    }

    /* Verifica duplicata no nível base */
    atual = atual->frente[0];
    if (atual && atual->valor == valor) {
        printf("[Aviso] Valor %d ja existe na Skip List. Ignorando.\n", valor);
        return;
    }

    /* Fase 2: sortear altura e ajustar nivel_atual  */
    int nova_altura = sl_nivel_aleatorio();

    /* Se o novo nó tiver mais níveis do que o atual máximo,
       os níveis extras têm a cabeça como predecessor */
    if (nova_altura > sl->nivel_atual) {
        for (i = sl->nivel_atual; i < nova_altura; i++) {
            atualizar[i] = sl->cabeca;
        }
        sl->nivel_atual = nova_altura;
    }

    /*  Fase 3: criar e encadear o novo nó  */
    No *novo = criar_no(valor, nova_altura);

    for (i = 0; i < nova_altura; i++) {
        /* novo->frente[i] aponta para onde atualizar[i] apontava */
        novo->frente[i] = atualizar[i]->frente[i];
        /* atualizar[i] passa a apontar para o novo nó */
        atualizar[i]->frente[i] = novo;
    }

    sl->tamanho++;
}


No *sl_buscar(SkipList *sl, int valor) {
    No *atual = sl->cabeca;
    int i;

    for (i = sl->nivel_atual - 1; i >= 0; i--) {
        /* Avança enquanto o próximo existe e é menor que o alvo */
        while (atual->frente[i] && atual->frente[i]->valor < valor) {
            atual = atual->frente[i];
        }
        /* Se o próximo for igual ao alvo, encontrou */
        if (atual->frente[i] && atual->frente[i]->valor == valor) {
            return atual->frente[i];
        }
        /* Caso contrário, desce um nível e continua */
    }

    return NULL; /* Não encontrado */
}


int sl_remover(SkipList *sl, int valor) {
    No *atualizar[MAX_NIVEL];
    No *atual = sl->cabeca;
    int i;

    /*  Fase 1: encontrar predecessores  */
    for (i = sl->nivel_atual - 1; i >= 0; i--) {
        while (atual->frente[i] && atual->frente[i]->valor < valor) {
            atual = atual->frente[i];
        }
        atualizar[i] = atual;
    }

    /* Candidato ao nó a remover */
    No *alvo = atualizar[0]->frente[0];

    /* Fase 2: verificar se realmente existe */
    if (!alvo || alvo->valor != valor) {
        return 0; /* Valor não encontrado */
    }

    /* Fase 3: desencadear o nó em cada nível  */
    for (i = 0; i < sl->nivel_atual; i++) {
        /* Se o predecessor neste nível não aponta para "alvo",
           então "alvo" não participa deste nível — pode parar */
        if (atualizar[i]->frente[i] != alvo) {
            break;
        }
        /* "Pula" o nó removido: predecessor aponta para o sucessor */
        atualizar[i]->frente[i] = alvo->frente[i];
    }

    /*  Fase 4: reduzir nivel_atual se ficou vazio no topo  */
    while (sl->nivel_atual > 0 &&
           sl->cabeca->frente[sl->nivel_atual - 1] == NULL) {
        sl->nivel_atual--;
    }

    free(alvo->frente);
    free(alvo);
    sl->tamanho--;

    return 1; 
}

void sl_imprimir(SkipList *sl) {
    if (sl->tamanho == 0) {
        printf("Skip List vazia.\n");
        return;
    }

    printf("\nEstrutura da Skip List (%d elemento(s))\n", sl->tamanho);
    int i;
    for (i = sl->nivel_atual - 1; i >= 0; i--) {
        printf("Nível %2d: [CAB]", i);
        No *atual = sl->cabeca->frente[i];
        while (atual) {
            printf(" --> %d", atual->valor);
            atual = atual->frente[i];
        }
        printf(" --> NULL\n");
    }
}

void sl_imprimir_nivel_base(SkipList *sl) {
    printf("Lista ordenada: ");
    No *atual = sl->cabeca->frente[0];
    if (!atual) {
        printf("(vazia)");
    }
    while (atual) {
        printf("%d ", atual->valor);
        atual = atual->frente[0];
    }
    printf("\n");
}


void sl_liberar(SkipList *sl) {
    No *atual = sl->cabeca->frente[0];
    while (atual) {
        No *proximo = atual->frente[0];
        free(atual->frente);
        free(atual);
        atual = proximo;
    }
    free(sl->cabeca->frente);
    free(sl->cabeca);

    sl->cabeca      = NULL;
    sl->nivel_atual = 0;
    sl->tamanho     = 0;
}
