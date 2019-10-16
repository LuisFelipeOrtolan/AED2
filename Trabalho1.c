  
/* 	Nome: Luís Felipe Corrêa Ortolan
	RA: 759375
	Universidade Federal de São Carlos - Algoritmos e Estruturas de Dados 2 (AED2).
	Programa que gerencia uma lista telefônica */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contatinho Contatinho;

struct contatinho{
	char nome[100];
	char telefone[10];
	Contatinho *prox;
};

static Contatinho **tabela = NULL; //Hashtable com encadeamento
static int tamanho; //Tamanho da hastable

/* 	Função de Hash.
	Input: Uma vetor de char com o nome do Contatinho e um inteiro que indica o tamanho da hashtable.
	Output: Um inteiro que indica em que posição da hashtable deve ser inserido o conatinho. */
int hash(char chave[], int tamanho){
	int i, h = 0;
	for(i = 0; chave[i] != '\0'; i++)
		h = h + 83 * chave[i];
	h = h % tamanho;	
	return h;
}

/* 	Função que inicializa HashTable.
	Input: Um inteiro que indica o tamanho da hashtable a ser criada.
	Output: A hashtable é criada. */
void inicializaHT(int _tam){
	tamanho = _tam;
	tabela = malloc(tamanho * sizeof(Contatinho *));
	for (int i = 0; i < tamanho; i++)
		tabela[i] = NULL;
}

/* 	Função que insere ou altera um Contatinho na HashTable.
	Input: Uma vetor de char com o nome do Contatinho, um vetor de char com o número do Contatinho e um parâmetro que é 0 se for inserção
																													  e 1 se for alteração.
	Output: Um Contatinho inserido na HashTable. */
void insereHT(char name[], char telefone[], int parametro){
	Contatinho *ptr;
	int chave = hash(name, tamanho);
	ptr = tabela[chave];
	while(ptr != NULL && strcmp(ptr->nome, name))
		ptr = ptr->prox;
	if(ptr == NULL){
		if(parametro == 0){
			ptr = malloc(sizeof(*ptr));
			strcpy(ptr->nome,name);
			ptr->prox = tabela[chave];
			tabela[chave] = ptr;
			strcpy(ptr->telefone,telefone);
		}
		else
			printf("Operacao invalida: contatinho nao encontrado\n");
	}
	else{
		if(parametro == 0)
			printf("Contatinho ja inserido\n");
		else
			strcpy(ptr->telefone,telefone);

	}
}
/* 	Função que procura um Contatinho na HashTable.
	Input: Uma vetor de char com o nome do Contatinho.
	Output: Impressão na tela do telefone do Contatinho buscado. */
void buscaHT(char name[]){
	int chave = hash(name,tamanho);
	Contatinho *ptr;
	ptr = tabela[chave];
	while(ptr != NULL && strcmp(ptr->nome, name) != 0)
		ptr = ptr->prox;
	if(ptr == NULL)
		printf("Contatinho nao encontrado\n");
	else
		printf("Contatinho encontrado: telefone %s\n", ptr->telefone);
}

/* 	Função que remove Contatinho da HashTable.
	Input: Uma vetor de char com o nome do Contatinho.
	Output: Contatinho removido da HashTable */
void removeHT(char name[]){
	Contatinho *ptr, *aux;
	int key = hash(name, tamanho);
	ptr = tabela[key];
	if(ptr == NULL){
		printf("Operacao invalida: contatinho nao encontrado\n");
		return;
	}
	if(strcmp(ptr->nome, name) == 0){
		tabela[key] = ptr->prox;
		free(ptr);
		return;
	}
	while(ptr->prox != NULL && strcmp((ptr->prox)->nome, name) != 0)
		ptr = ptr->prox;
	if(ptr->prox != NULL){
		aux = ptr->prox;
		ptr->prox = aux->prox;
		free(aux);
	}
	else{
		printf("Operacao invalida: contatinho nao encontrado\n");
		return;
	}
	
}

/* 	Função que encerra a HashTable.
	Input: Nenhum.
	Output: A HashTable é encerrada */
void finalizaHT(){
	Contatinho *p = NULL, *q = NULL;
	for (int i = 0; i < tamanho; i++){
		p = tabela[i];
		while (p != NULL){
			q = p;
			p = p->prox;
			free(q);
		}
	}
	free(tabela);
	tabela = NULL;
}

/* 	Função de Hash.
	Input: Uma linha de comando com operações definidas: I - inserção/ P - procura/ R - remoção/ A - alteração/ 0 - finalizar.
	Output: 1 se a execução do programa deve continuar e 0 se a execução deve ser encerrada. */
int interpretador(){
	char comando;
	char *nome;
	char *telefone;

	nome = malloc(sizeof(char ) * 100);
	telefone = malloc(sizeof(char ) * 10);

	scanf("%c ", &comando);

	if(comando == 'I'){
		scanf("%s %s", nome, telefone);
		insereHT(nome,telefone, 0);
	}
	else if(comando == 'P'){
		scanf("%s", nome);
		buscaHT(nome);
	}
	else if(comando == 'R'){
		scanf("%s", nome);
		removeHT(nome);
	}
	else if(comando == 'A'){
		scanf("%s %s", nome, telefone);
		insereHT(nome,telefone, 1);
	}
	else if(comando == '0'){
		free(nome);
		free(telefone);
		finalizaHT();
		return 0;
	}
	free(nome);
	free(telefone);
	return 1;
}


int main(){
	inicializaHT(100); //Inicializa uma HashTable com tamanho 100.
	while (interpretador()); //Loop até o interpretador retornar que deve ser encerrada a execução.
	return 0;
}