#include <stdio.h>
#include <stdlib.h>

int func_A(int n){
    int c = 0;  //--------------------------------------------1
    int i = 0;  //--------------------------------------------1
    for(i=1; i <= n;i++){//--------------------------------------SOMAT�RIO- LS: N, LI: i = 1, Termo: 1, logo, igual a N
    	c += 1; //--------------------------------------------1
	}
	int j = 0;  //--------------------------------------------1
	for(j=1; j <= n; j++){//--------------------------------------SOMAT�RIO- LS: N, LI: j = 1, Termo: 1, logo, igual a N
		c += 2; //--------------------------------------------1
	}
	
	return c;
}

//Logo, nossa T(n) = 1+1+N+1+N = 2n + 3
//Olhando a T(n), a Fun��o A � de complexidade Big O(n)

int func_B(int n){
	int c = 0; //---------------------------------------------1
	int i = 0; //---------------------------------------------1
	
	for(i=1; i <= n;i++){ //-------------------------------------------------SOMAT�RIO- LS: N, LI: i = 1, Termo: 1 + SOMAT�RIO INTERNO
		int j = 0; //----------------------------------------------1
		for(j=1; j <= n; j++){ //----------------------------------SOMAT�RIO- LS: N, LI: j = 1, Termo: 1, logo, igual a N
			c = c + 1; //-------------------------------------1
		}	
	}
	return c;
}
// Neste caso, a T(n) = 1 + 1 + SOMAT�RIO - LS: N, LI: i=1, Termo: 1 + SOMAT�RIO - LS: N, LI: j=1, Termo: 1
// Logo, o somat�rio interno, vira N.
//Ent�o temos, T(n) = 1 + 1 + SOMAT�RIO - lS: N, LI: i=1, Termo: 1 + N.
// T(n) = 2 + N + N� 
// Big O(N�)


int func_C(int n){
	int c = 0; //----------------------------------------------------------1
	int i = 0; //----------------------------------------------------------1
	for(i = 1; i < n; i++){//---------------------------------------------SOMAT�RIO- LS: N, LI: i = 1, Termo: 1 + SOMAT�RIO INTERNO.
		int j = 1;//-------------------------------------------1
		for(j = i; j < n; j++){//------------------------------SOMAT�RIO- LS: i, LI: j = i, Termo: 1
			c += 1;//-------------------------------1
		}
	}
	return c;
}

//observe que, o for interno executa uma soma de P.A vezes, por que ?
// quando o i = 0, o For interno com o j, ir� de 0 � N, ou seja, N vezes
// quando o i = 1, o For interno com o j, ir� de 1 � N, ou seja, N-1 vezes
// quando o i = 2, o For interno com o j, ir� de 2 � N, ou seja, N-2 vezes
//at�....
// quando o i = N, o For interno com o j, ir� de N � N, ou seja, 1 vez

// Temos que, a original T(n) = 1 + 1 + SOMAT�RIO- LS: N, LI: i = 1, Termo: 1 + SOMAT�RIO- LS: N, LI: j = i, Termo: 1
// Se transforma ent�o em: T(n) = 1 + 1 + SOMAT�RIO- LS: N, LI: i = 1, Termo: 1 + i
// Ao final, seguindo a solu��o com P.A e a regra, fica: 
// T(n) = N.(1 + N)/2 + N + 2 
// T(n) = N�/2 + n/2 + N + 2
// Note que, em "N.(1 + N)/2", segue a regra Sn = N/2.(x1 + xN), logo, o x1 � 1 e xN � N.
// Big O(N�)

int func_D(int n){ //Sucessivas divis�es por 2 (log na base 2, quanto maior a base, mais r�pido)
	int c = 0; // ---------------------------------------------1
	int i = n; // ---------------------------------------------1
	while ( i > 1){ // ----------------------------------------K = [log n]
		c += 1; //---------------------------------------- 1
		i = i / 2; //------------------------------------- 1
	}
	return c;
}
// Essa fun��o calcula quantas vezes o numero pode ser dividido por 2, at� que atinja 0.
// n = 16 -> 8 -> 4 -> 2 -> 1
// nesse exemplo, a variavel C termina valendo 4, pois 2^4 = 16
// n = 40 -> 20 -> 10 -> 5 -> 2 -> 1
// neste outro, a variavel c termina a fun��o valendo 5, pois 2^5 < 40 < 2^6
// Portanto, o numero de itera��es do loop � log2 n. 
// Temos a T(n) = 2 + 2[log2 n], sendo a fun��o piso(x), retornando o maior inteiro menor que x.
// Big O(log2 n)

// Note que x, � o valor resultante da divis�o, se este valor � decimal, ele pega a maior parte inteira menor que o n�mero.
// se for 2,5, ser� 2. se for -3,4 ser� -4, por que -4 � o maior inteiro menor que -4 (-4 esta mais a esquerda na reta numerica)


int func_E(n){
	int c = 0; //----------------------------------------------------------1
	int i = 0; //----------------------------------------------------------1
	for(i = 0; i < n; i++){ //---------------------------------------------SOMAT�RIO- LS: N, LI: i = 1, Termo: log2 n
		c = c + func_D(n);// ----------------log2 n (por que a atribui��o, que realiza a chamada de outra fun��o, assume a complexidade da fun��o.
	}
	return c;
}
//Logo temos, T(n) = SOMAT�RIO- LS: N, LI: i = 1, Termo: log2 n, o log2 n � independente, podemos inverte-lo na fun��o.
// ficando assim: T(n) = log2 n . SOMAT�RIO- LS: N, LI: i = 1, Termo: 1 (ou seja, N)
// Portanto, a T(n) = n log2 n + 2
// Big O(n log n)

void main(){
	int n = 10;
	int c = func_A(n);
	printf("Funcao A resultado: %d \n", c);
	c = func_B(n);
	printf("Funcao B resultado: %d \n", c);
	c = func_C(n);
	printf("Funcao C resultado: %d \n", c);
	c = func_D(n);
	printf("Funcao D resultado: %d \n", c);
	c = func_E(n);
	printf("Funcao E resultado: %d \n", c);
	
}
