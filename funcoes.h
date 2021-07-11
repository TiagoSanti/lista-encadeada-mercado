/****************************************************
* Tiago Clarintino Santi
* Trabalho
* Professor(a): Graziela Santos de Araujo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//registro de compra
typedef struct lista_c
{
	int cod;
	float preco;
	int qtde;
	struct lista_c *prox;
} listaCompra;

//registro de produtos
typedef struct lista_p
{
	int cod;
	char nome[30];
	float preco;
	int qtde;
	int I;
	struct lista_p *ant;
	struct lista_p *prox;
} listaProd;

//registro de vendas
typedef struct lista_v
{
	char data[11];
	char hora[9];
	char cpf[13];
	float total;
	struct lista_c *lst;
	struct lista_v *ant;
	struct lista_v *prox;
} listaVendas;

//função que cadastra a venda
void cadastrar(listaVendas **V, listaProd **P);

//função que altera preço e quantidade de um produto
void alterar(listaProd **lst);

//função que insere os produtos na lista de produtos a partir de um arquivo .txt
void inserir_prod(int cod, char *nome, float preco, int qtde, listaProd **P);

//função que remove um nó de uma lista duplamente encadeada
void remover_dupl(listaProd **P, listaProd *p);

//função que lista as vendas de uma data indicada
void listar(listaVendas **V);

//função que remove um produto da lista de produtos
void remover(listaProd **P);

//função que verifica a existência de um produto na lista de produtos
listaProd *busca(int cod, listaProd *P);

//funções que desalocam listas
void desalocar_v(listaVendas **V);
void desalocar_p(listaProd **P);
void desalocar_c(listaCompra **C);