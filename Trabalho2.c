/* 	Nome: Luís Felipe Corrêa Ortolan
	RA: 759375
	Universidade Federal de São Carlos - Algoritmos e Estruturas de Dados 2 (AED2).
	Input: Uma linha com 3 parâmetros iniciais: N - Número de linhas e colunas de uma matriz de distâncias; 
												K - Número do vizinho limite para outlier;
												L - Limiar para outlier;
	Output: Número de outliers.*/

#include <stdio.h>
#include <stdlib.h>

/* 	Função que troca valor de dois doubles.	
	Input: Dois endereços de doubles.
	Output: Os conteúdos das variáveis foram trocados entre si. */
void trocaD(double *a, double *b){
	double aux;
	aux = *b;
	*b = *a;
	*a = aux;
}

/* 	Função que separa um vetor em maiores que o último elemento e menores que o último elemento.	
	Input: Um vetor de doubles, um inteiro que indica a posição de início do vetor e um inteiro que  indica a posição final do vetor.
	Output: Um inteiro dizendo em que posição o elemento que foi usado como pivô se encontra agora. */
int separa(double vetor[], int ini, int fim){
	int i = ini, pivo = vetor[fim];
	for(int j = ini; j < fim; j++)
		if(vetor[j] <= pivo){
			trocaD(&vetor[i], &vetor[j]);
			i++;
		}
	trocaD(&vetor[i], &vetor[fim]);
	return i;
}

/* 	Função que pega o elemento da posição pos de um vetor quando ele está ordenado.
	Input: Um vetor de doubles, um inteiro com o número de itens de um vetor e um inteiro que indica a posição que se deseja obter. 
	Output: Um double que é o valor que está na posição pos do vetor quando ele está ordenado. */
double selecao(double vetor[], int tam, int pos){
	int deslocamento, i;
	int ini = 0, fim = tam - 1;
	do{
		deslocamento = rand() % (fim - ini + 1);
		trocaD(&vetor[deslocamento + ini], &vetor[fim]);
		i = separa(vetor, ini, fim);
		if (pos < i)
			fim = i - 1;
		else
			ini = i + 1;
	} while(pos != i);

	return vetor[i];
}

int main(){

	//Abertura de Arquivo
	FILE *arq;
	char nomeArquivo[100];
	scanf("%s", nomeArquivo);	
	arq = fopen(nomeArquivo, "r");
	if(arq == NULL){ //Se falhar
		printf("Nao foi possível abrir o arquivo\n");
		return 0;
	}
	// Se chegou aqui, arquivo aberto com sucesso.
	int n, k; 
	int outliers = 0; //Número de outliers
	double limiar;
	double nro;
	double *vetor;

	fscanf(arq, "%d %d %lf", &n, &k, &limiar); //Leitura dos parâmetros iniciais
	vetor = (double *)malloc(sizeof(double) * n); // Alocação do veetor de doubles

	for (int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			fscanf(arq, "%lf ", &nro);
			vetor[j] = nro;
		}
		
		nro = selecao(vetor, n, k+1); //Seleciona o k-esimo elemento do vetor sem considerar ele mesmo.
		if (nro > limiar) // Se for maior que o limiar, então é outlier.
			outliers++;
	}

	printf("%d\n", outliers);
}