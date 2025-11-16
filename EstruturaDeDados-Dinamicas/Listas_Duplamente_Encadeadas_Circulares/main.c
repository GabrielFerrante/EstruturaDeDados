#include <stdio.h>
#include "circular_doubly_list.c"
#include <locale.h>

int main() {
	setlocale(LC_ALL, "portuguese");
    CircularList cl;
    init(&cl);

    printf("=== TESTANDO LISTA CIRCULAR DUPLAMENTE ENCADEADA ===\n\n");

    // Testando adição no início
    printf("1. Adicionando no início:\n");
    add_head(&cl, 30);
    add_head(&cl, 20);
    add_head(&cl, 10);
    display_forward(&cl);
    display_backward(&cl);
    printf("\n");

    // Testando adição no final
    printf("2. Adicionando no final:\n");
    add_tail(&cl, 40);
    add_tail(&cl, 50);
    display_forward(&cl);
    display_backward(&cl);
    printf("\n");

    // Testando busca
    printf("3. Testando busca:\n");
    int search_key = 20;
    Node* found = search(&cl, search_key);
    if (found != NULL) {
        printf("Chave %d encontrada!\n", search_key);
    } else {
        printf("Chave %d não encontrada!\n", search_key);
    }
    
    search_key = 99;
    found = search(&cl, search_key);
    if (found != NULL) {
        printf("Chave %d encontrada!\n", search_key);
    } else {
        printf("Chave %d não encontrada!\n", search_key);
    }
    printf("\n");

    // Testando inserção entre nós
    printf("4. Inserindo entre nós (após 20):\n");
    add_between(&cl, 20, 25);
    display_forward(&cl);
    display_backward(&cl);
    printf("\n");

    // Testando remoção do meio
    printf("5. Removendo do meio (25):\n");
    remove_node(&cl, 25);
    display_forward(&cl);
    display_backward(&cl);
    printf("\n");

    // Testando remoção do início
    printf("6. Removendo do início (10):\n");
    remove_node(&cl, 10);
    display_forward(&cl);
    display_backward(&cl);
    printf("\n");

    // Testando remoção do final
    printf("7. Removendo do final (50):\n");
    remove_node(&cl, 50);
    display_forward(&cl);
    display_backward(&cl);
    printf("\n");

    // Testando remoção de elemento inexistente
    printf("8. Tentando remover elemento inexistente (99):\n");
    printf("Resultado: %s\n", remove_node(&cl, 99) ? "Sucesso" : "Falha");
    display_forward(&cl);
    display_backward(&cl);
    printf("\n");

    free_list(&cl);
    return 0;
}
