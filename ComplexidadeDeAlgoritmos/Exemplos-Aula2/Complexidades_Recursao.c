#include <stdlib.h>
#include <stdio.h>


long long int fibonacci(int n){
	if(n==0){
		return 0;
	}else{
		if(n==1){
			return 1;
		}else{
			return fibonacci(n-1) + fibonacci(n-2); // Dupla recurs�o.
		}
	}
}
//Para medir a complexidade utilizar a t�cnica de rela��o de recorr�ncia.
//Passo 1 : Dividir em sub problemas
//Passo 2 : Abrir a recorr�ncia at� encontrar um padr�o
//Passo 3: Generalizar para um K arbitr�rio.
//Passo 4: Validar condi��o de parada
//Temos inicialmente:
//T(n) = T(n-1) + T(n-2) + O(1), note que o O(1), � a opera��o de soma.
//Neste caso, podemos simplificar, partindo do pressuposto, que a complexidade T(n-1) � pr�ximo de T(n-2), em caso de n seja grande.
//T(n) =  2.T(n-1) + 1
//Agora, iremos compreender o que � T(n-1):
//T(n-1) = 2.T(n-2) + 1
//Portanto, a T(n) fica:
//T(n) = 2 [ 2.T(n-2)+1] + 1
//Abrindo T(n-2), fica:
//T(n) = 2 { 2 [ 2.T(n-3) + 1] + 1 } + 1
//A T(n) acima, pode ser traduzida para:
//T(n) = 2� . T(n-3) + [1 + 2� + 2�], note que o �ltimo termo, � um somat�rio, sendo o expoente variando.
//Portanto, de forma gen�rica, para um K arbitr�rio
//T(n) = 2^k . T(n-k) + SOMAT�RIO- LS:k-1, LI:i=0, Termo: 2^i
//Para resolver este somat�rio, temos que usar o m�todo da soma telesc�pica.
//Antes disso, precisamos saber a seguinte jogada matem�tica, onde 2^i+1 = 2.2^i = 2^i + 2^i
//logo, 2^i = 2^i+1 - 2^i, assim temos um somat�rio de subtra��o.
//Portanto, fica: SOMAT�RIO- LS: k-1, LI: i=0, Termo: (2^i+1 - 2^i), 
//aplicando a soma telesc�pica, 
//o limite superior k-1 substitui o exponencial i+1 do primeiro termo da subtra��o, e o limite inferior i=0, substitui o segundo termo 2^i
//Transformando o somat�rio em 2^k - 1.
//Voltando, a T(n) = 2^k.T(n-k)+(2^k-1)
//Vamos verificar a condi��o de parada para T(0)
//n-k tem que ser igual a 0, para isso, k tem que ser igual a n.
//Portanto, T(n) = 2^n . T(0)(ou seja, 1) + 2^n - 1
//Ficando: T(n) = 2.2^n . -1
//logo: T(n) = 2^n+1 - 1
//Nosso Big O(2^n) exponencial, ou seja, p�ssimo em efici�ncia.

void main(){
	
	int n = 50;
	long long int resultado = fibonacci(n);
	printf("Fibonacci: %lld \n", resultado);
	system("PAUSE");
	
}
