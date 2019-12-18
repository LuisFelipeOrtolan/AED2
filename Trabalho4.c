/* 	Nome: Luís Felipe Corrêa Ortolan
	RA: 759375
	Universidade Federal de São Carlos - Algoritmos e Estruturas de Dados 2 (AED2).
	Input: Uma linha com o número de nós e arestas em um grafo e linhas com os vértices de ida e de chegada das arestas e seus custos.
	Output: A menor distância do primeiro até o último vértice. */


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct noh Noh;
struct noh {
 int rotulo; //Número do vértice.
 int custo; //Custo de uma aresta.
 Noh *prox; //Próximo nó.
};


typedef struct grafo *Grafo;
struct grafo{
	Noh **A;
	int n; //Número de vértices.
	int m; //Número de arestas.
};

/*	Função que inicializa um Grafo com listas de adjacências.
	Input: Um inteiro n com o número de vértices desse grafo.
	Output: Um Grafo inicializado. */
Grafo inicializaGrafo(int n){
	Grafo G = malloc(sizeof *G);
	G->n = n;
	G->m = 0;
	G->A = malloc(n * sizeof(Noh *));
	for(int i = 0; i < n; i++)
		G->A[i] = NULL;
	return G;
}

/*	Função que insere arcos em um grafo.
	Input: O grafo em que a aresta vai ser inserida, um inteiro que indica
							o vértice v de saída e um inteiro que indica o vértice w de chegada do arco e um inteiro com o custo desse arco.
	Output: O grafo agora tem mais uma aresta. */
void insereArcoGrafo(Grafo G, int v, int w, int custo){
	Noh *p;
	for(p = G->A[v]; p != NULL; p = p->prox) //Verifica se o arco já não foi inserido.
		if(p->rotulo == w)
			return;
	p = malloc(sizeof(Noh)); //Aloca um novo nó.
	p->rotulo = w; //Atribui o rótulo do novo nó.
	p->custo = custo; //Atribui o custo do novo nó.
	p->prox = G->A[v]; //Coloca o novo nó na lista de arcos do nó v.
	G->A[v] = p;
	G->m++; //Aumenta o número de arcos no grafo.
}

/*	Função que libera um grafo com listas de adjacências.
	Input: Um grafo.
	Output: Um ponteiro para NULL. */
Grafo freeGrafo(Grafo G){
	Noh *p;
	for(int i = 0; i < G->n; i++){ //Percorre todos os nós.
		p = G->A[i];
		while(p != NULL){ //Percorre a lista de cada vértice.
			G->A[i] = p;
			p = p->prox;
			free(G->A[i]); //Desalocando os nós alocados para aquele nó.
		}
		G->A[i] = NULL; 
	}

	free(G->A);
	G->A = NULL;
	free(G);
	return NULL;
}

/*	Função que implementa o algoritmo de Dijkstra.
	Input: Um grafo, um inteiro com o rótulo do vértice de origem e um vetor de inteiros de tamanho n, que terá as distâncias da origem até cada vértice.
	Output: Um vértice com todas as distâncias da origem a cada vértice. */
void algoritmoDijkstra(Grafo G, int origem, int *distancia){
	int i;
	int *resolvidos;
	int v, w, custo, tam_R, distanciaMin;
	Noh *p;

	for(i = 0; i < G->n; i++){ //Preparos iniciais.
		distancia[i] = INT_MAX; //Coloca a maior distância possível.
	}

	distancia[origem] = 0; //Distância da origem em relação a ela mesmo é 0.

	resolvidos = malloc(G->n * sizeof(int)); //Vetor auxiliar para saber quais já foram resolvidos.
	
	for(i = 0; i < G->n; i++) //Marca inicialmente como nenhum resolvido.
		resolvidos[i] = 0;
	tam_R = 0;

	while(tam_R < G->n){ //Enquanto todos não tiverem sido resolvidos.
		distanciaMin =  INT_MAX; //Distância mínima começa em infinito.
		v = -1; //E o vetor a ser trabalhado em -1.
		for(i = 0; i < G->n; i++){ //Percorre todos os nós.
			if(resolvidos[i] == 0 && distancia[i] < distanciaMin){ //Procurando um que não tenha sido resolvido e que tenha distância menor que a mínima.
				v = i; //Atualiza o vetor a ser trabalhado.
				distanciaMin = distancia[i]; //Atualiza a distância mínima.
			}
		}

		resolvidos[v] = 1; //Marca como resolvido.
		tam_R++; //Aumenta o tamanho dos resolvidos.
		p = G->A[v]; 
		if(v == -1){ //Se não foi encontrado nenhum nó para ser trabalhado, encerra.
			return;
		}
		while(p != NULL){ //Enquanto não acabar os arcos daquele nó.
			w = p->rotulo; //W recebe o rótulo daquele nó.
			custo = p->custo; //custo recebe o custo daquele arco.
			if(resolvidos[w] == 0 && distancia[w] > distancia[v] + custo){ //Se a nova distância for menor que a atual,
				distancia[w] = distancia[v] + custo; //Atualiza o custo do novo nó.
			}
			p = p->prox; //Avança na lista.
		}
	}

	free(resolvidos);
}


int main(){
	int n, m;

	scanf("%d %d", &n, &m);
	Grafo G = inicializaGrafo(n);

	int A,B,W;

	for(int i = 0; i < m; i++){
		scanf("%d %d %d", &A, &B, &W);
		insereArcoGrafo(G, A, B, W);
	}

	int *distancia;

	distancia = malloc(G->n * sizeof(int));

	algoritmoDijkstra(G, 0, distancia);

	printf("%d", distancia[n-1]);

	G = freeGrafo(G);

	return 0;
}