/* 	Nome: Luís Felipe Corrêa Ortolan
	RA: 759375
	Universidade Federal de São Carlos - Algoritmos e Estruturas de Dados 2 (AED2).
	Input: Uma linha com o tamanho de caracteres do texto e o tamanho da palavra buscada no texto, uma segunda linha com o texto e uma terceira linha com a palavra. 
	Output: As posições onde a palavra foi encontrada. */

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

/*	Função que pré processa uma palavra para uso no algoritmo de BoyerMoore com a ideia do GoodSufix.
	Input: Um vetor de bytes com a palavra e um inteiro com tamanho dessa palavra.
	Output: Um vetor de inteiros ... */
int *preProcessamento1(byte a[], int m){
	int *jump = malloc ((m+1) * sizeof (int));
	int h = m; 
	int k = m - 1;
	int i = m; 
	int j = m - 1;
	while (h >= 1) { 
   		while (i >= h && j >= 1)  
      		if (a[i - 1] == a[j - 1]){
      			--i; 
      			--j;
      		}
      		else{ 
      			i = m; 
      			j = --k;
      		}
   		jump[h--] = k;
	}

	return jump;
}

/*	Função que pré processa uma palavra para uso no algoritmo de BoyerMoore com a ideia do BadCharacter.
	Input: Um vetor de bytes com a palavra a ser buscada em um texto e um int com o seu tamanho.
	Output: Um vetor de inteiros com quantos bytes devem ser pulados se ocorrer determinado valor no alfabeto, no caso 0 a 9. */
int *preProcessamento2(byte palavra[], int tam){
	int i;
	int *dist_ult = malloc(10 * sizeof(int));
	for(i = 0; i < 10; ++i)
		dist_ult[i] = 0; //Inicialmente marca todos os caracteres como a distância da palavra.
	for(i = 1; i <= tam; ++i)
		dist_ult[palavra[i]] = i; //Depois passa por todos os caracteres da palavra e ajusta o tamanho a ser pulado.

	return dist_ult;
}

/*	Função que executa o algoritmo de BoyerMoore para busca de uma palavra em um texto.
	Input: Um vetor de bytes que é a palavra buscada, um inteiro com o tamanho da palavra buscada, um vetor de bytes com o texto completo e um inteiro com o tamanho do texto.
	Output: É impresso na tela todas as posições das ocorrências do texto. */
void BoyerMoore(byte palavra[], int tamP, byte texto[], int tamT) {
 	int *alcance, *dist_ult; //Vetores de inteiros para pré processamento.
 	int posTexto, incr1, incr2;
 	dist_ult = preProcessamento2(palavra, tamP); //Pré Processamento Bad Character.
 	alcance = preProcessamento1(palavra, tamP); //Pré Processamento Good Sufix.
 	posTexto = tamP; //Posição do texto começa no tamanho da palavra, pois é onde pode ocorrer a primeira vez a palavra.
 	while (posTexto <= tamT - 1) {
 		int i = tamP, j = posTexto;
 		while (i >= 1 && palavra[i - 1] == texto[j - 1]){
 			i--, j--;
 		}
 		if (i < 1)
 			printf("%d\n",posTexto - tamP);
 		if (posTexto == tamT)
 			incr1 = 1;
		else
 			incr1 = tamP - dist_ult[texto[posTexto]];
 		if (i == tamP)
 			incr2 = 1;
 		else
 			incr2 = tamP - alcance[tamP];
		if(incr1 > incr2)
			posTexto = posTexto + incr1;
		else
			posTexto = posTexto + incr2;
 	}
 	free(dist_ult);
 	free(alcance);
}

int main(){
	FILE *arq;
	char nomeArquivo[100];
	scanf("%s", nomeArquivo);

	arq = fopen(nomeArquivo, "r");

	if(arq == NULL)
		return 0;

	int tamT = 0, tamP = 0;

	fscanf(arq, "%d %d\n", &tamT, &tamP);

	byte *texto;
	byte *palavra;

	texto = malloc(tamT * sizeof(unsigned char));
	palavra = malloc(tamP * sizeof(unsigned char));

	fscanf(arq, "%s\n", &texto[0]);
	fscanf(arq, "%s\n", &palavra[0]);

	BoyerMoore(palavra,tamP,texto,tamT);

	free(texto);
	free(palavra);
	return 0;
}