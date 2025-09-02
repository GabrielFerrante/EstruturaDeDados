#include <stdio.h>   // Biblioteca para entrada/sa�da (printf, etc.)
#include <stdlib.h>  // Biblioteca para aloca��o de mem�ria (malloc, free, realloc)
#include <string.h>  // Biblioteca para manipula��o de strings (strlen, memmove, memset)
#include <math.h>    // Biblioteca para fun��es matem�ticas (fmax, fmin)

// Estrutura para representar n�meros grandes com d�gitos armazenados em ordem reversa
typedef struct {
    int* digits;   // Array de d�gitos (ordem reversa: d�gito menos significativo primeiro)
    int length;    // N�mero atual de d�gitos no array
} BigInt;

// Prot�tipos das fun��es
void freeBigInt(BigInt* n);  // Libera mem�ria alocada para BigInt
BigInt* addBigInt(BigInt* a, BigInt* b);  // Soma dois BigInts
void shiftLeft(BigInt* n, int places);  // Desloca d�gitos (multiplica por 10^places)
BigInt* createBigIntFromString(const char* s);  // Cria BigInt a partir de string
long long toLong(BigInt* n);  // Converte BigInt para long long
BigInt* fromLong(long long val);  // Cria BigInt a partir de long long
void printBigInt(BigInt* n);  // Imprime BigInt na ordem correta

// Fun��o de multiplica��o usando divis�o e conquista (4 parti��es)
BigInt* multiply_4_partitions(BigInt* a, BigInt* b) {
    // Determina o tamanho do maior n�mero
    int n = fmax(a->length, b->length);

    // Caso base: n�meros pequenos, converte para long long para multiplica��o direta
    if (n <= 4) {
        long long val_a = toLong(a);
        long long val_b = toLong(b);
        return fromLong(val_a * val_b);
    }
    
    // Calcula ponto de divis�o (metade do tamanho)
    int mid = n / 2;

    // Cria vis�es (views) das metades sem copiar dados
    BigInt* a1 = malloc(sizeof(BigInt));  // Parte alta de a
    BigInt* a2 = malloc(sizeof(BigInt));  // Parte baixa de a
    BigInt* b1 = malloc(sizeof(BigInt));  // Parte alta de b
    BigInt* b2 = malloc(sizeof(BigInt));  // Parte baixa de b

    // Configura parte baixa de a (primeiros 'mid' d�gitos)
    a2->length = fmin(mid, a->length);
    a2->digits = a->digits;  // Aponta para in�cio do array original

    // Configura parte baixa de b (primeiros 'mid' d�gitos)
    b2->length = fmin(mid, b->length);
    b2->digits = b->digits;  // Aponta para in�cio do array original

    // Configura parte alta de a (d�gitos restantes)
    a1->length = a->length > mid ? a->length - mid : 0;
    //A linha usa um operador tern�rio para determinar o comprimento de `a1`. A condi��o �:
	// Se o comprimento de `a` for maior que `mid`, ent�o a parte alta `a1` ter� comprimento `a->length - mid`.
	//Caso contr�rio (se o comprimento de `a` for menor ou igual a `mid`), ent�o a parte alta `a1` ter� comprimento 0.
   
    a1->digits = a->digits + mid;  // Aponta para metade do array original

    // Configura parte alta de b (d�gitos restantes)
    b1->length = b->length > mid ? b->length - mid : 0;
    b1->digits = b->digits + mid;  // Aponta para metade do array original

    // Chamadas recursivas para as 4 multiplica��es:
    BigInt* A = multiply_4_partitions(a1, b1);  // a1 * b1
    BigInt* B = multiply_4_partitions(a1, b2);  // a1 * b2
    BigInt* C = multiply_4_partitions(a2, b1);  // a2 * b1
    BigInt* D = multiply_4_partitions(a2, b2);  // a2 * b2

    // Calcula soma B + C
    BigInt* sum_BC = addBigInt(B, C);
    
    // Desloca A para esquerda por 2*mid posi��es (multiplica por 10^(2*mid))
    shiftLeft(A, 2 * mid);
    // Desloca soma B+C para esquerda por mid posi��es (multiplica por 10^mid)
    shiftLeft(sum_BC, mid);

    // Soma os componentes deslocados
    BigInt* partial_result = addBigInt(A, sum_BC);
    BigInt* final_result = addBigInt(partial_result, D);
    
    // Libera mem�ria das estruturas tempor�rias
    free(a1); free(a2); free(b1); free(b2);
    freeBigInt(A);
    freeBigInt(B);
    freeBigInt(C);
    freeBigInt(D);
    freeBigInt(sum_BC);
    freeBigInt(partial_result);

    return final_result;
}

// Fun��o principal de teste
int main() {
    // Cria n�meros grandes a partir de strings
    BigInt* num1 = createBigIntFromString("123456789");
    BigInt* num2 = createBigIntFromString("987654321");

    // Imprime os n�meros
    printf("Numero 1: "); printBigInt(num1);
    printf("Numero 2: "); printBigInt(num2);
    
    // Calcula produto usando multiplica��o por parti��es
    BigInt* product = multiply_4_partitions(num1, num2);

    // Imprime resultado
    printf("Produto:  "); printBigInt(product);

    // Libera mem�ria final
    freeBigInt(num1);
    freeBigInt(num2);
    freeBigInt(product);

    return 0;
}

// Remove zeros n�o significativos � esquerda (fim do array na representa��o reversa)
void trim(BigInt* n) {
    while (n->length > 1 && n->digits[n->length - 1] == 0) {
        n->length--;
    }
}

// Cria BigInt a partir de string
BigInt* createBigIntFromString(const char* s) {
    int len = strlen(s);
    if (len == 0) {  // Trata string vazia como zero
        len = 1;
        s = "0";
    }
    BigInt* n = malloc(sizeof(BigInt));
    n->digits = malloc(sizeof(int) * len);
    n->length = len;
    // Preenche array na ordem reversa (d�gito menos significativo primeiro)
    int i = 0;
    for (i = 0; i < len; i++) {
        n->digits[i] = s[len - 1 - i] - '0';  // Converte char para int
    }
    trim(n);  // Remove zeros n�o significativos
    return n;
}

// Libera mem�ria de BigInt
void freeBigInt(BigInt* n) {
    if (n) {
        free(n->digits);  // Libera array de d�gitos
        free(n);          // Libera estrutura
    }
}

// Imprime BigInt na ordem correta (do mais significativo para o menos)
void printBigInt(BigInt* n) {
    if (!n) {
        printf("(null)\n");
        return;
    }
    // Imprime do �ltimo d�gito (mais significativo) para o primeiro
    int i = 0;
    for (i = n->length - 1; i >= 0; i--) {
        printf("%d", n->digits[i]);
    }
    printf("\n");
}

// Soma dois BigInts
BigInt* addBigInt(BigInt* a, BigInt* b) {
    int maxLen = fmax(a->length, b->length);
    BigInt* result = malloc(sizeof(BigInt));
    result->digits = calloc(maxLen + 1, sizeof(int));  // Aloca com zeros
    result->length = maxLen;
    int carry = 0;
    int i = 0;
    for (i = 0; i < maxLen; i++) {
        // Obt�m d�gitos de a e b (ou 0 se acabaram)
        int d1 = (i < a->length) ? a->digits[i] : 0;
        int d2 = (i < b->length) ? b->digits[i] : 0;
        int sum = d1 + d2 + carry;
        result->digits[i] = sum % 10;  // D�gito resultante
        carry = sum / 10;              // Carry para pr�xima posi��o
    }
    if (carry > 0) {  // Se sobrou carry, aumenta tamanho
        result->digits[maxLen] = carry;
        result->length = maxLen + 1;
    }
    return result;
}

// Desloca d�gitos para esquerda (adiciona zeros no final na representa��o reversa)
void shiftLeft(BigInt* n, int places) {
    if ((n->length == 1 && n->digits[0] == 0) || places == 0) return;
    int new_len = n->length + places;
    n->digits = realloc(n->digits, sizeof(int) * new_len);
    // Move d�gitos existentes para o final
    memmove(n->digits + places, n->digits, n->length * sizeof(int));
    // Preenche in�cio com zeros
    memset(n->digits, 0, places * sizeof(int));
    n->length = new_len;
}

// Converte BigInt para long long (apenas para n�meros pequenos)
long long toLong(BigInt* n) {
    long long val = 0;
    // Percorre do mais significativo para o menos (ordem reversa no array)
    int i = n->length - 1;
    for (i = n->length - 1; i >= 0; i--) {
        val = val * 10 + n->digits[i];
    }
    return val;
}

// Cria BigInt a partir de long long
BigInt* fromLong(long long val) {
    char buffer[30];  // Buffer para convers�o
    sprintf(buffer, "%lld", val);
    return createBigIntFromString(buffer);
}
