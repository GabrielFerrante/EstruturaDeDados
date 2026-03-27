# Algoritmos e Estrutura de Dados

Este repositório contém materiais e exemplos relacionados aos principais conceitos de Estrutura de Dados, fundamentais para o desenvolvimento eficiente de algoritmos e aplicações.

**Códigos criados e revisados por Gabriel Souto Ferrante | Aluno de estágio PESCD** 
- Conteúdos referentes as disciplinas de AED1 (02/2025) e AED2 (01/2026) da Universidade Federal de São Carlos.

## Material de apoio


**Manual Completo de algoritmos e estrutura de dados - Prof. Dr. Alexandre Levada  (UFSCAR)**.
**DOI: 10.13140/RG.2.2.11875.87847**

## Conteúdos Abordados

#### 1. Complexidade de Algoritmos
A complexidade de um algoritmo é uma métrica crucial para avaliar seu desempenho em termos de tempo e espaço. Entender a complexidade de um algoritmo nos ajuda a prever seu comportamento à medida que o tamanho da entrada cresce, permitindo a escolha da solução mais eficiente para um problema.
- **Conceitos:** Notação Big O, tempo de execução constante O(1), linear O(n), quadrático O(n²), logarítmico O(log n) e linearítmico O(n log n).

#### 2. Recursão
Recursão é uma técnica de programação onde uma função chama a si mesma para resolver um problema. A ideia principal é dividir um problema grande em subproblemas menores, até que um "caso base" seja alcançado, que pode ser resolvido diretamente sem mais chamadas recursivas. É um conceito fundamental em muitos algoritmos, incluindo travessias de árvores e ordenação.

#### 3. Algoritmos de Ordenação
Algoritmos de ordenação são fundamentais para organizar dados. Eles recebem uma lista ou array e reordenam seus elementos em uma sequência específica.
- **Bubblesort:** Um algoritmo simples que repetidamente percorre a lista, compara elementos adjacentes e os troca se estiverem na ordem errada.
- **Insertionsort:** Constrói a lista final ordenada um item de cada vez. É eficiente para pequenos conjuntos de dados.
- **Selectionsort:** Encontra o menor elemento da lista e o move para a primeira posição, repetindo o processo para o restante dos elementos.
- **Shellsort:** Uma versão aprimorada do Insertion Sort.
- **Quicksort:** Um algoritmo de divisão e conquista que seleciona um 'pivô' e particiona a lista em torno dele.
- **Mergesort (Ordenação por intercalação):** Também um algoritmo de divisão e conquista que divide a lista ao meio, ordena cada metade e as mescla.
- **Limite Inferior para Ordenação Baseada em Comparações:** Demonstra que, no melhor caso, a complexidade de tempo de qualquer algoritmo de ordenação baseado em comparações é O(n log n).
- **Ordenação Não Baseada em Comparações:**
    - **Countingsort:** Funciona contando a frequência de cada elemento na lista.
    - **Radixsort:** Ordena números inteiros processando seus dígitos um por um.
    - **Bucketsort:** Divide o array em um número de "baldes" e ordena cada um deles individualmente.

---

#### 4. Tipos Abstratos de Dados (TAD's)
Um TAD é um modelo matemático para um tipo de dado. Ele define o comportamento (as operações) do dado, mas não a sua implementação subjacente. Exemplos comuns incluem listas, pilhas e filas.

#### 5. Estruturas de Dados Lineares Estáticas
São estruturas com tamanho fixo, ou seja, a alocação de memória é definida no momento da compilação e não pode ser alterada durante a execução.
- **Pilhas (LIFO - Last In, First Out):** O último elemento a entrar é o primeiro a sair. Exemplo: a pilha de pratos na cantina.
- **Filas (FIFO - First In, First Out):** O primeiro elemento a entrar é o primeiro a sair. Exemplo: uma fila de espera.
- **Deque (Fila de duas extremidades):** Uma fila generalizada onde a inserção e a remoção podem ocorrer em ambas as extremidades.
- **Fila de prioridades (Priority Queue):** Uma fila onde cada elemento tem uma prioridade associada, e a ordem de remoção depende dessa prioridade.

#### 6. Estruturas de Dados Dinâmicas
Diferentemente das estáticas, essas estruturas têm sua alocação de memória ajustada durante o tempo de execução.
- **Listas encadeadas:** Uma coleção de elementos (nós) onde cada nó contém um dado e um ponteiro para o próximo nó da sequência.
- **Listas encadeadas ordenadas:** Cada novo elemento é inserido na posição correta para manter a lista sempre ordenada.
- **Listas duplamente encadeadas:** Cada nó contém ponteiros para o nó anterior e para o próximo, permitindo a travessia em ambas as direções.
- **Aplicações:** Exemplos práticos incluem matrizes esparsas, listas ortogonais e matrizes dinâmicas.

---

#### 7. Árvores Binárias
Uma estrutura de dados hierárquica que consiste em nós conectados. Cada nó tem no máximo dois filhos, um à esquerda e um à direita.

#### 8. Árvores Binárias de Busca
Uma árvore binária com uma propriedade de ordenação: para cada nó, todos os valores na subárvore esquerda são menores, e todos os valores na subárvore direita são maiores.

#### 9. Estruturas de Dados: Árvores AVL (Balanceadas)
Uma Árvore Binária de Busca que é "auto-balanceável". A diferença de altura entre as subárvores esquerda e direita de qualquer nó é no máximo 1, garantindo operações eficientes de busca, inserção e remoção.

#### 10. Estruturas de Dados: Heaps binários
Uma árvore binária completa que satisfaz a propriedade de heap, onde o valor de um nó pai é sempre maior ou igual (max-heap) ou menor ou igual (min-heap) ao de seus filhos.
- **O algoritmo Heapsort:** Um algoritmo de ordenação que usa a estrutura de dados Heap para ordenar os elementos.

#### 11. Estruturas de Dados: Árvores de Busca Digitais (Tries)
Também conhecidas como árvores de prefixos, são usadas para armazenar e buscar strings de forma eficiente. As chaves não são armazenadas nos nós, mas sim codificadas no caminho da raiz até o nó.

#### 12. Estruturas de Dados: Árvores Rubro-Negras
Outra árvore de busca binária auto-balanceável. Garante que a altura da árvore seja sempre O(log n), mantendo a eficiência das operações mesmo após inserções e remoções.

#### 13. Estruturas de Dados: Skip Lists
Uma estrutura de dados probabilística baseada em listas encadeadas, que utiliza "camadas" de listas para acelerar as operações de busca.

#### 14. Estruturas de Dados: Tabelas de Espalhamento (Hash Tables)
Uma estrutura de dados que associa chaves a valores, usando uma função de hash para calcular um índice em um array de "baldes" ou "slots". Oferece busca, inserção e remoção em tempo médio constante O(1).

#### 15. Estruturas de Dados: O Filtro de Bloom
Uma estrutura de dados probabilística e com eficiência de espaço, usada para testar se um elemento é um membro de um conjunto. Pode ter falsos positivos, mas nunca falsos negativos.

---

#### 16. Grafos: Fundamentos Básicos
Um grafo é uma estrutura de dados não linear que consiste em um conjunto de vértices (nós) e arestas (conexões) que os unem.
- **Busca em Grafos (BFS e DFS):**
    - **Busca em Largura (Breadth-First Search - BFS):** Percorre o grafo por nível, explorando todos os vizinhos de um nó antes de passar para o próximo nível.
    - **Busca em Profundidade (Depth-First Search - DFS):** Percorre o grafo o mais "profundamente" possível ao longo de cada ramo antes de retroceder.
- **Caminhos Mínimos e o Algoritmo de Dijkstra:** Encontra o caminho mais curto entre dois nós em um grafo com arestas ponderadas (custos).
- **Árvores geradoras mínimas:** Uma subárvore de um grafo que conecta todos os vértices com o menor custo total de arestas.
    - **Algoritmo de Kruskal:** Constrói a árvore geradora mínima adicionando arestas de menor peso que não formam um ciclo.
    - **Algoritmo de Prim:** Constrói a árvore geradora mínima adicionando o vértice mais próximo ao conjunto já construído.
- **Fluxo em redes e o algoritmo de Ford-Fulkerson:** Resolve o problema de fluxo máximo em redes, que busca o máximo de "fluxo" que pode passar de uma fonte para um destino.
- **O Problema do Caixeiro Viajante (Traveling Salesman Problem - TSP):** Um problema de otimização NP-difícil que busca o caminho mais curto para um caixeiro que precisa visitar várias cidades e retornar à cidade de origem.

---