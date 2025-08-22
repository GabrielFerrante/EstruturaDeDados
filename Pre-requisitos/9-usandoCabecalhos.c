#include "9-usandoCabecalhos.h"
#include <stdio.h>

// Função para inicializar um Funcionario
void inicializarFuncionario(Funcionario *f, int id, const char *nome, float salario) {
    f->id = id;
    snprintf(f->nome, sizeof(f->nome), "%s", nome); 
	//A fun��o snprintf() formata e armazena uma s�rie de caracteres e valores na matriz buffer. 
	//Qualquer lista de argumentos � convertido e colocado de acordo com a especifica��o de formato correspondente no format-string.. 
	//A fun��o snprintf() � id�ntica � fun��o sprintf() com a adi��o do argumento n , 
	//que indica o n�mero m�ximo de caracteres (incluindo o caractere nulo final) a ser gravado no buffer..
    f->salario = salario;
}

// Função para imprimir os dados de um Funcionario
void imprimirFuncionario(const Funcionario *f) {
    printf("ID: %d\n", f->id);
    printf("Nome: %s\n", f->nome);
    printf("Salario: %.2f\n", f->salario);
}

// Função para atualizar o salário de um Funcionario
void atualizarSalario(Funcionario *f, float novoSalario) {
    f->salario = novoSalario;
}

