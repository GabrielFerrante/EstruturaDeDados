#include <stdio.h>


int obterMaior(int array[], int tamanho) {
    int maior = array[0];
    int i;
    for (i = 1; i < tamanho; i++) {
        if (array[i] > maior)
            maior = array[i];
    }
    return maior;
}


void countingSortR(int array[], int tamanho, int exp) {
    int output[tamanho]; // Array auxiliar com o resultado ordenado
    int count[10] = {0};  // Contagem dos digitos (0 a 9)
    int i;

    // Conta quantas vezes cada digito aparece na posicao atual
    for (i = 0; i < tamanho; i++) {
        int digito = (array[i] / exp) % 10;
        count[digito]++;
    }

    // Acumula as contagens (prefixo) para saber a posicao final
    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Constroi o array de saida percorrendo de tras pra frente
    //    (isso garante a ESTABILIDADE da ordenacao)
    for (i = tamanho - 1; i >= 0; i--) {
        int digito = (array[i] / exp) % 10;
        output[count[digito] - 1] = array[i];
        count[digito]--;
    }

    // Copia o resultado de volta para o array original
    for (i = 0; i < tamanho; i++) {
        array[i] = output[i];
    }
}

void radixSort(int array[], int tamanho) {
    // Descobre o maior valor para saber quantos digitos processar
    int maior = obterMaior(array, tamanho);

    // Executa o counting sort para cada posicao de digito
    // exp vai de 1 (unidade) ate o digito mais significativo
    int exp;
    for (exp = 1; maior / exp > 0; exp *= 10) {
        countingSortR(array, tamanho, exp);
    }
}

void imprimirArray(int array[], int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int tamanho = sizeof(arr) / sizeof(arr[0]);

    printf("Array original: ");
    imprimirArray(arr, tamanho);

    radixSort(arr, tamanho);

    printf("Array ordenado: ");
    imprimirArray(arr, tamanho);

    return 0;
}
