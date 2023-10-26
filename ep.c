//--------------------------------------------------------------
// NOMES DOS RESPONSÁVEIS: blablabla E blablabla
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <limits.h>

int grupo() {
  return 0;
}

// ######### ESCREVA O NROUSP AQUI
int nroUSP1() {
    return 0;
}

int nroUSP2() {
    return 0;
}

// elemento das listas de adjacência e de resposta - NAO ALTERE ESTA DEFINICAO
typedef struct estr 
{
      int adj; // elemento
	int peso; // custo (não precisa ser usado na resposta)
      struct estr *prox;
} NO;

// vertices do grafo (salas) - use este tipo ao criar o grafo  - NAO ALTERE ESTA DEFINICAO
typedef struct 
{
       int flag; // para uso na busca em largura e profundidade, se necessario
       bool aberto; // vale true se a sala em questao esta aberta
       int via; // use este campo se precisar computar algum caminho etc.
	 int dist; // use este campo se precisar computar alguma distância etc.
       NO* inicio;
} VERTICE;


// funcao principal
NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave);


//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO* caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave) {
	// Criação do grafo em listas de adjacência
	VERTICE* grafo = (VERTICE*) malloc((N + 1) * sizeof(VERTICE));
	for (int i = 1; i <= N; i++) {
		grafo[i].flag = 0;
		grafo[i].aberto = (aberto[i] == 1);
		grafo[i].via = 0;
		grafo[i].dist = INT_MAX;
		grafo[i].inicio = NULL;
	}

	for (int i = 0; i < 3 * A; i += 3) {
		int origem = ijpeso[i];
		int destino = ijpeso[i + 1];
		int peso = ijpeso[i + 2];

		// Adiciona a aresta no vértice de origem
		NO* novo = (NO*) malloc(sizeof(NO));
		novo->adj = destino;
		novo->peso = peso;
		novo->prox = grafo[origem].inicio;
		grafo[origem].inicio = novo;

		// Adiciona a aresta no vértice de destino (grafo não dirigido)
		novo = (NO*) malloc(sizeof(NO));
		novo->adj = origem;
		novo->peso = peso;
		novo->prox = grafo[destino].inicio;
		grafo[destino].inicio = novo;
	}

	// Algoritmo de Dijkstra
	grafo[inicio].dist = 0;

	for (int i = 1; i <= N; i++) {
		// Encontra o vértice não visitado com menor distância
		int minDist = INT_MAX;
		int minVertice = -1;
		for (int j = 1; j <= N; j++) {
			if (!grafo[j].flag && grafo[j].dist < minDist) {
				minDist = grafo[j].dist;
				minVertice = j;
			}
		}

		if (minVertice == -1)
			break;

		// Marca o vértice como visitado
		grafo[minVertice].flag = 1;

		// Atualiza as distâncias dos vértices adjacentes
		NO* adjacente = grafo[minVertice].inicio;
		while (adjacente != NULL) {
			int verticeAdjacente = adjacente->adj;
			int pesoAresta = adjacente->peso;

			if (!grafo[verticeAdjacente].flag && grafo[minVertice].dist != INT_MAX && grafo[minVertice].dist + pesoAresta < grafo[verticeAdjacente].dist) {
				grafo[verticeAdjacente].dist = grafo[minVertice].dist + pesoAresta;
				grafo[verticeAdjacente].via = minVertice;
			}

			adjacente = adjacente->prox;
		}
	}

	// Construção do caminho mínimo
	if (grafo[fim].dist != INT_MAX) {
		NO* resp = NULL;
		int verticeAtual = fim;
		while (verticeAtual != inicio) {
			NO* novo = (NO*) malloc(sizeof(NO));
			novo->adj = verticeAtual;
			novo->prox = resp;
			resp = novo;
			verticeAtual = grafo[verticeAtual].via;
		}

		// Adiciona o vértice de início ao caminho mínimo
		NO* novo = (NO*) malloc(sizeof(NO));
		novo->adj = inicio;
		novo->prox = resp;
		resp = novo;

		return resp;
	}

	return NULL; // Não há caminho possível
}



//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {


	// aqui vc pode incluir codigo de teste

	// exemplo de teste trivial
	int N=3; // grafo de 3 vértices numerados de 1..3
	int A = 3;
  int aberto[] = {1,1,1}; // todos abertos
	int inicio=1;
	int fim=3;
	int chave=2;
	int ijpeso[]={1,2,10, 2,3,20, 3,1,10};
	// o EP sera testado com uma serie de chamadas como esta
	NO* teste = NULL;
	teste = caminho(N, A, ijpeso, aberto, inicio, fim, chave);
	return teste;
  while (teste->prox != NULL)
  printf ("%i", teste->adj);
}

// por favor nao inclua nenhum código abaixo da função main()

