#ifndef HASH_H
#define HASH_H

#define TAMANHO 11  /* primo para melhor distribuicao */

typedef struct No {
    int chave;
    struct No *proximo;
} No;

typedef struct {
    No *tabela[TAMANHO];
    int total;
} TabelaHash;

void    hash_init(TabelaHash *h);
int     hash_func(int chave);
void    hash_insert(TabelaHash *h, int chave);
No     *hash_search(TabelaHash *h, int chave);
int     hash_remove(TabelaHash *h, int chave);
void    hash_print(TabelaHash *h);
void    hash_free(TabelaHash *h);

#endif
