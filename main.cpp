#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

// elemento das listas de adjacência e de resp - NAO ALTERE ESTA DEFINICAO
typedef struct estr {
  int adj;           // elemento
  int peso;          // custo (não precisa ser usado na resp)
  struct estr *prox; // indica o prox elemento do caminho
} NO;

// vertices do grafo (salas) - use este tipo ao criar o grafo  - NAO ALTERE ESTA
// DEFINICAO
typedef struct {
  int flag;    // utilizado para indicar se o vertice ja foi descoberto
  bool aberto; // vale true se a sala em questao esta aberta
  int via;     // utilizado para guardar o cmainho
  int dist;    // utilizado para o calculo da distancia
  NO *inicio;
} VERTICE;

// funcao principal
NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim,
            int chave);

// função para inicializar a matriz
void initMatrizAdj(int **matriz, int *ijpeso, int A) {
  for (int i = 0; i < 3 * A; i += 3) {
    int vertice1 = ijpeso[i];
    int vertice2 = ijpeso[i + 1];
    matriz[vertice1][vertice2] = ijpeso[i + 2];
    matriz[vertice2][vertice1] = ijpeso[i + 2];
  }
}

// função para imprimir a matriz
void printMatrizAdj(int **MatrizADJ, int N) {
  for (int i = 0; i < N + 1; i++) {
    for (int j = 0; j < N + 1; j++)
      printf("%i ", MatrizADJ[i][j]);
    printf("\n");
  }
}

// função que retorna a distância do caminho minho
// Se o selecionador for 1 guardará o caminho no NO ** resp
int dijkstra(int N, int **MatrizADJ, VERTICE *vertices, int inicio, int fim,
             int selecionador, NO **resp) {
  for (int i = 0; i < N + 1; i++) {
    vertices[i].dist = INT_MAX;
    vertices[i].flag = 0;
  }

  vertices[inicio].dist = 0;

  for (int i = 1; i < N + 1; i++) {
    int minDist = INT_MAX;
    int minVertice = -1;
    for (int j = 1; j < N + 1; j++) {
      if (!vertices[j].flag && vertices[j].dist < minDist &&
          vertices[j].aberto) {
        minDist = vertices[j].dist;
        minVertice = j;
      }
    }
    if (minVertice == -1)
      break;
    vertices[minVertice].flag = 1; // marca o vértice como visitado

    for (int j = 1; j < N + 1; j++) {
      if (!vertices[j].flag && MatrizADJ[minVertice][j] != 0 &&
          vertices[j].aberto) {
        int novaDist = vertices[minVertice].dist + MatrizADJ[minVertice][j];
        if (novaDist < vertices[j].dist ||
            vertices[j].dist == INT_MAX && vertices[j].aberto) {
          vertices[j].dist = novaDist;
          vertices[j].via = minVertice;
        }
      }
    }
  }

  if (vertices[fim].dist == INT_MAX)
    return -1;

  if (selecionador == 1) {
    int atual = fim;
    int caminho[N];
    int tamanhoCaminho = 0;

    while (atual != inicio) {
      caminho[tamanhoCaminho++] = atual;
      atual = vertices[atual].via;
    }

    caminho[tamanhoCaminho++] = inicio;

    NO *melhorCaminho = NULL;
    NO *p = NULL;
    for (int i = tamanhoCaminho - 1; i >= 0; i--) {
      NO *novo = (NO *)malloc(sizeof(NO));
      novo->adj = caminho[i];
      novo->prox = NULL;
      if (melhorCaminho == NULL) {
        melhorCaminho = novo;
        p = novo;
      } else {
        p->prox = novo;
        p = p->prox;
      }
    }
    *resp = melhorCaminho;
  }

  return vertices[fim].dist;
}

// Junta as 2 listas ligadas do caminho1 (inicio -> chave) e caminho2
// (chave -> fim) e retorna um terceiro caminho
NO *juntaCaminhos(NO *caminho1, NO *caminho2) {
  if (caminho1 == NULL)
    return caminho2;
  if (caminho2 == NULL)
    return caminho1;

  NO *ultimoCaminho1 = caminho1;
  while (ultimoCaminho1->prox != NULL) {
    ultimoCaminho1 = ultimoCaminho1->prox;
  }

  ultimoCaminho1->prox =
      caminho2
          ->prox; // Conecta o último nó de caminho1 ao segundo nó de caminho2

  free(caminho2); // Libera a memória alocada para o segundo nó de caminho2

  return caminho1;
}

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim,
            int chave) {
  NO *resp;
  resp = NULL;
  if (inicio > N || inicio < 1 || fim > N || fim < 1)
    return resp;
  if (chave <= 0)
    chave = -10; // apenas para facilitar algumas operações
  VERTICE *vertices = (VERTICE *)malloc(sizeof(VERTICE) * (N + 1));
  int **MatrizADJ = (int **)calloc((N + 1), sizeof(int *));
  // Troca de i=0 para i=1
  // Troca de vertices[i].aberto = aberto[i] para vertices[i].aberto =
  // aberto[i-1]
  for (int i = 1; i < N + 1; i++) {
    MatrizADJ[i] = (int *)calloc((N + 1), sizeof(int));
    vertices[i].flag = 0;
    vertices[i].aberto = aberto[i - 1];
    vertices[i].via = 0;
    vertices[i].dist = INT_MAX;
    vertices[i].inicio = NULL;
  }

  initMatrizAdj(MatrizADJ, ijpeso, A);

  int distSemChave = dijkstra(N, MatrizADJ, vertices, inicio, fim, 0, &resp);

  int distAteChave = 0;
  distAteChave += dijkstra(N, MatrizADJ, vertices, inicio, chave, 0, &resp);

  for (int i = 1; i < N + 1; i++) {
    vertices[i].aberto = 1;
  }

  int distChaveDestino = 0;
  distChaveDestino += dijkstra(N, MatrizADJ, vertices, chave, fim, 0, &resp);
  int distComChave = distAteChave + distChaveDestino;

  // Troca de vertices[i].aberto = aberto[i] para vertices[i].aberto =
  // aberto[i-1]
  for (int i = 1; i < N + 1; i++) {
    vertices[i].aberto = aberto[i - 1];
  }
  if (distAteChave != -1 && distChaveDestino != -1 && distSemChave == -1) {
    NO *wayToKey = NULL;
    NO *wayKeyToEnd = NULL;

    dijkstra(N, MatrizADJ, vertices, inicio, chave, 1, &wayToKey);

    for (int i = 1; i < N + 1; i++) {
      vertices[i].aberto = 1;
    }

    dijkstra(N, MatrizADJ, vertices, chave, fim, 1, &wayKeyToEnd);
    // Troca de vertices[i].aberto = aberto[i] para vertices[i].aberto =
    // aberto[i-1]
    for (int i = 1; i < N + 1; i++) {
      vertices[i].aberto = aberto[i - 1];
    }
    resp = juntaCaminhos(wayToKey, wayKeyToEnd);
  } else if (((distAteChave == -1 && distChaveDestino == -1) || chave <= 0) &&
             distSemChave != -1) {
    dijkstra(N, MatrizADJ, vertices, inicio, fim, 1, &resp);

  } else if (distAteChave != -1 && distChaveDestino != -1 &&
             distSemChave != -1) {
    if (distComChave >= distSemChave) {
      dijkstra(N, MatrizADJ, vertices, inicio, fim, 1, &resp);
    } else {
      NO *wayToKey = NULL;
      NO *wayKeyToEnd = NULL;

      dijkstra(N, MatrizADJ, vertices, inicio, chave, 1, &wayToKey);

      for (int i = 1; i < N + 1; i++) {
        vertices[i].aberto = 1;
      }

      dijkstra(N, MatrizADJ, vertices, chave, fim, 1, &wayKeyToEnd);
      // Troca de vertices[i].aberto = aberto[i] para vertices[i].aberto =
      // aberto[i-1]
      for (int i = 1; i < N + 1; i++) {
        vertices[i].aberto = aberto[i - 1];
      }
      resp = juntaCaminhos(wayToKey, wayKeyToEnd);
    }
  }

  free(vertices);
  for (int i = 0; i < N + 1; i++) {
    free(MatrizADJ[i]);
  }
  free(MatrizADJ);
  return resp;
}

//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {
  int N = 11; // grafo de 11 vértices numerados de 1 a 11
  int A = 15;
  int aberto[] = {0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1}; // vértice 3 e 5 fechados
  int inicio = 8;
  int fim = 6;
  int chave = 3;
  int ijpeso[] = {1, 2, 1, 1, 4, 2, 1, 6, 1, 1, 8, 4, 2, 3, 4,
                  2, 4, 2, 2, 8, 1, 2, 9, 5, 3, 4, 1, 3, 5, 1,
                  4, 5, 1, 5, 6, 2, 6, 7, 1, 7, 8, 2, 8, 9, 2};
  // o EP sera testado com uma serie de chamadas como esta
  NO *teste = NULL;
  teste = caminho(N, A, ijpeso, aberto, inicio, fim, chave);
  if (teste == NULL)
    printf("Vetor nulo");
  NO *noAtual = teste;
  while (noAtual != NULL) {
    printf("%d ", noAtual->adj);
    noAtual = noAtual->prox;
  }
}
