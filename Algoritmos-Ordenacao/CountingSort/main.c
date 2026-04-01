#include <stdio.h>
#include <stdlib.h>


// Função auxiliar para encontrar o maior valor do array
int encontrarMaximo(int array[], int tamanho) {
    int max = array[0];
    int i;
    for (i = 1; i < tamanho; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

void countingSort(int array[], int tamanho) {
    // Passo 1: Descobrir o maior valor para saber o tamanho do array de contagem
    int max = encontrarMaximo(array, tamanho);

    // Passo 2: Criar o array de contagem (índices de 0 até max)
    // Cada posição vai guardar quantas vezes aquele valor aparece
    int *contagem = (int *)calloc(max + 1, sizeof(int));

    // Criar o array de saída que vai receber os elementos ordenados
    int *saida = (int *)malloc(tamanho * sizeof(int));

    // Passo 3: Contar a frequência de cada elemento
    int i;
    for (i = 0; i < tamanho; i++) {
        contagem[array[i]]++;
    }

    // Passo 4: Acumular as contagens (soma prefixada)
    // Isso nos diz quantos elementos são MENORES OU IGUAIS a cada valor,
    // ou seja, a posição final de cada elemento no array ordenado
    for (i = 1; i <= max; i++) {
        contagem[i] += contagem[i - 1];
    }

    // Passo 5: Construir o array de saída
    // Percorremos o array original de trás para frente (para manter estabilidade)
    // Para cada elemento, usamos contagem[] para saber sua posição correta
    for (i = tamanho - 1; i >= 0; i--) {
        saida[contagem[array[i]] - 1] = array[i];
        contagem[array[i]]--;  // Decrementa para o próximo elemento igual
    }

    // Passo 6: Copiar o resultado de volta para o array original
    for (i = 0; i < tamanho; i++) {
        array[i] = saida[i];
    }

    // Liberar a memória alocada dinamicamente
    free(contagem);
    free(saida);
}

void imprimirArray(int array[], int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {4, 2, 2, 8, 3, 3, 1, 7, 5, 4};
    int tamanho = sizeof(arr) / sizeof(arr[0]);

    printf("Array original:  ");
    imprimirArray(arr, tamanho);

    countingSort(arr, tamanho);

    printf("Array ordenado:  ");
    imprimirArray(arr, tamanho);

    return 0;
}
