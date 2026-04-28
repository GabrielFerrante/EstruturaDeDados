#ifndef DST_H
#define DST_H

// Numero de bits da chave (w bits)
// Usando int de 32 bits, mas podemos ajustar conforme necessidade
#define W 8

// Estrutura do no da Arvore de Busca Digital
typedef struct NoDST {
    int key;                // Chave armazenada com w bits
    struct NoDST* p;        // Ponteiro para o no pai
    struct NoDST* Child[2]; // Child[0] = filho esquerdo (bit 0)
                            // Child[1] = filho direito  (bit 1)
} NoDST;

// --- Operacoes basicas ---
NoDST* criar_no(int key, NoDST* pai);
NoDST* inserir(NoDST* raiz, int key);
NoDST* buscar(NoDST* raiz, int key);
NoDST* remover(NoDST* raiz, int key);

// --- Operacoes auxiliares ---
int obter_bit(int key, int posicao);
void imprimir_bits(int key);
void em_ordem(NoDST* raiz);
void pre_ordem(NoDST* raiz);
void liberar(NoDST* raiz);

#endif
