#include <stdio.h>
#include <stdlib.h>
#include "dst.h"

/*
 * Extrai o bit na posicao dada de uma chave.
 *
 * A posicao 0 corresponde ao bit mais significativo (MSB) dentro dos W bits.
 * Exemplo com W=8 e key=5 (binario: 00000101):
 *   posicao 0 -> bit 7 (MSB) -> 0
 *   posicao 5 -> bit 2       -> 1
 *   posicao 6 -> bit 1       -> 0
 *   posicao 7 -> bit 0 (LSB) -> 1
 *
 * Formula: desloca a chave (W - 1 - posicao) bits para a direita
 *          e aplica mascara & 1 para isolar o bit.
 */
int obter_bit(int key, int posicao) {
    return (key >> (W - 1 - posicao)) & 1;
}

/*
 * Imprime a representacao binaria de uma chave com W bits.
 * Util para visualizar como os bits determinam o caminho na arvore.
 */
void imprimir_bits(int key) {
    int i;
    for (i = 0; i < W; i++) {
        printf("%d", obter_bit(key, i));
    }
}

/*
 * Cria um novo no da DST com a chave fornecida.
 * Inicializa ambos os filhos como NULL e define o ponteiro para o pai.
 *
 * Complexidade: O(1)
 */
NoDST* criar_no(int key, NoDST* pai) {
    NoDST* novo = (NoDST*)malloc(sizeof(NoDST));
    if (novo == NULL) {
        printf("Erro: falha na alocacao de memoria!\n");
        return NULL;
    }

    novo->key = key;
    novo->p = pai;
    novo->Child[0] = NULL; // Filho para bit 0
    novo->Child[1] = NULL; // Filho para bit 1

    return novo;
}

/*
 * Insere uma chave na Arvore de Busca Digital.
 *
 * Funcionamento:
 *   - Se a arvore esta vazia, a chave se torna a raiz.
 *   - Caso contrario, percorremos a arvore examinando o bit da chave
 *     correspondente ao nivel atual:
 *       * No nivel 0 -> examina o bit mais significativo (posicao 0)
 *       * No nivel 1 -> examina o proximo bit (posicao 1)
 *       * ... e assim por diante
 *   - Se o bit eh 0, segue para Child[0]; se eh 1, segue para Child[1].
 *   - Quando encontramos um Child NULL, inserimos o novo no ali.
 *
 * Complexidade: O(W) no pior caso, onde W = numero de bits da chave
 */
NoDST* inserir(NoDST* raiz, int key) {
    // Arvore vazia: novo no se torna a raiz (pai = NULL)
    if (raiz == NULL) {
        printf("Inserindo %d (", key);
        imprimir_bits(key);
        printf(") como raiz\n");
        return criar_no(key, NULL);
    }

    NoDST* atual = raiz;
    int nivel = 0;

    while (nivel < W) {
        // Extrai o bit da chave na posicao correspondente ao nivel
        int bit = obter_bit(key, nivel);

        // Se o filho na direcao do bit esta vazio, inserimos aqui
        if (atual->Child[bit] == NULL) {
            atual->Child[bit] = criar_no(key, atual);

            printf("Inserindo %d (", key);
            imprimir_bits(key);
            printf(") -> nivel %d, bit %d, filho de %d\n", nivel, bit, atual->key);

            return raiz;
        }

        // Senao, desce para o filho correspondente
        atual = atual->Child[bit];
        nivel++;
    }

    // Se chegou aqui, todos os W niveis foram percorridos sem encontrar espaco
    printf("Erro: nao foi possivel inserir %d (chave duplicada ou colisao)\n", key);
    return raiz;
}

/*
 * Busca uma chave na DST.
 *
 * Percorre a arvore bit a bit:
 *   - Em cada nivel, examina o bit correspondente da chave buscada
 *   - Compara a chave do no atual com a chave buscada
 *   - Se encontrar, retorna o no
 *   - Se chegar em NULL, a chave nao existe
 *
 * Complexidade: O(W) no pior caso
 */
NoDST* buscar(NoDST* raiz, int key) {
    NoDST* atual = raiz;
    int nivel = 0;

    while (atual != NULL) {
        // Se a chave do no atual eh a que procuramos, encontramos!
        if (atual->key == key) {
            return atual;
        }

        // Extrai o bit e desce na direcao correspondente
        int bit = obter_bit(key, nivel);
        atual = atual->Child[bit];
        nivel++;
    }

    // Chave nao encontrada
    return NULL;
}

/*
 * Encontra um no folha na subarvore (usado pela remocao).
 * Desce sempre pelo primeiro filho disponivel ate encontrar uma folha.
 *
 * Complexidade: O(W) no pior caso
 */
NoDST* encontrar_folha(NoDST* no) {
    if (no == NULL) return NULL;

    // Se nao tem filhos, eh folha
    if (no->Child[0] == NULL && no->Child[1] == NULL) {
        return no;
    }

    // Desce pela esquerda primeiro; se nao tiver, pela direita
    if (no->Child[0] != NULL) {
        return encontrar_folha(no->Child[0]);
    }
    return encontrar_folha(no->Child[1]);
}

/*
 * Remove uma chave da Arvore de Busca Digital.
 *
 * Tres casos possiveis:
 *   1. No eh folha (sem filhos):
 *      -> Remove diretamente e atualiza o ponteiro do pai
 *
 *   2. No tem filhos:
 *      -> Encontra uma folha na subarvore do no a ser removido
 *      -> Copia a chave da folha para o no atual
 *      -> Remove a folha (que eh o caso simples 1)
 *
 *   3. Chave nao encontrada:
 *      -> Nao faz nada
 *
 * Complexidade: O(W) no pior caso
 */
NoDST* remover(NoDST* raiz, int key) {
    // Busca o no com a chave a ser removida
    NoDST* alvo = buscar(raiz, key);

    if (alvo == NULL) {
        printf("Chave %d nao encontrada para remocao.\n", key);
        return raiz;
    }

    // Se o no tem filhos, precisamos de um substituto
    // Encontramos uma folha na subarvore e trocamos as chaves
    while (alvo->Child[0] != NULL || alvo->Child[1] != NULL) {
        NoDST* folha = encontrar_folha(alvo);
        alvo->key = folha->key; // Copia a chave da folha para o no atual
        alvo = folha;           // Agora vamos remover a folha
    }

    // Neste ponto, 'alvo' eh uma folha — podemos remover com seguranca

    // Atualiza o ponteiro do pai
    if (alvo->p != NULL) {
        // Descobre se 'alvo' eh Child[0] ou Child[1] do pai
        if (alvo->p->Child[0] == alvo) {
            alvo->p->Child[0] = NULL;
        } else {
            alvo->p->Child[1] = NULL;
        }
        free(alvo);
    } else {
        // O no removido era a raiz (e era folha = unico no)
        free(alvo);
        return NULL;
    }

    return raiz;
}

/*
 * Percurso em ordem (in-order): Child[0] -> no -> Child[1]
 * Como a DST nao garante ordenacao como uma BST, este percurso
 * mostra a estrutura da arvore mas nao necessariamente em ordem crescente.
 *
 * Complexidade: O(n), onde n = numero de nos
 */
void em_ordem(NoDST* raiz) {
    if (raiz == NULL) return;

    em_ordem(raiz->Child[0]);

    printf("  Chave: %3d | Bits: ", raiz->key);
    imprimir_bits(raiz->key);
    printf(" | Pai: ");
    if (raiz->p != NULL) {
        printf("%d", raiz->p->key);
    } else {
        printf("NULL (raiz)");
    }
    printf("\n");

    em_ordem(raiz->Child[1]);
}

/*
 * Percurso pre-ordem com indentacao para visualizar a estrutura.
 * Mostra a hierarquia: raiz primeiro, depois Child[0], depois Child[1].
 *
 * Complexidade: O(n), onde n = numero de nos
 */
void pre_ordem(NoDST* raiz) {
    if (raiz == NULL) return;

    // Calcula a profundidade usando o ponteiro para o pai
    int profundidade = 0;
    NoDST* temp = raiz;
    while (temp->p != NULL) {
        profundidade++;
        temp = temp->p;
    }

    // Indentacao proporcional a profundidade
    int i;
    for (i = 0; i < profundidade; i++) {
        printf("    ");
    }

    printf("[%d] (", raiz->key);
    imprimir_bits(raiz->key);
    printf(")\n");

    pre_ordem(raiz->Child[0]);
    pre_ordem(raiz->Child[1]);
}

/*
 * Libera toda a memoria da arvore (percurso pos-ordem).
 *
 * Complexidade: O(n)
 */
void liberar(NoDST* raiz) {
    if (raiz == NULL) return;

    liberar(raiz->Child[0]);
    liberar(raiz->Child[1]);
    free(raiz);
}
