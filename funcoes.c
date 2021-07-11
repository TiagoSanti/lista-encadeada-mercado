/***************************************************
* Tiago Clarintino Santi
* Trabalho
* Professor(a): Graziela Santos de Araujo
*/

#include "funcoes.h"

void cadastrar(listaVendas **V, listaProd **P)
{
	listaVendas *Vnovo = NULL;
	listaProd *p, *q;
	listaCompra *Cnovo = NULL, *c;
	p = *P;
	int cod, qtde;
	char i;

	if(p == NULL)
		printf("Nenhum produto em estoque.\n\n");

	else
	{
		//inserindo venda no início da lista de vendas
		Vnovo = (listaVendas*) malloc(sizeof(listaVendas));
		Vnovo->ant = NULL;
		Vnovo->prox = *V;
		*V = Vnovo;
		Vnovo->lst = NULL;

		printf("Data (aaaa/mm/dd) : "); scanf(" %s", Vnovo->data);
	    printf("Hora (hh:mm:ss)   : "); scanf(" %s", Vnovo->hora);
	    printf("CPF (XXXXXXXXX-XX): "); scanf(" %s", Vnovo->cpf);
	    printf("\n");
		
		//impressão dos produtos
		while(p != NULL)
		{
			printf("Codigo: %d\n"
				   "Nome: %s\n"
				   "Preco: %.2f\n\n", p->cod, p->nome, p->preco);
			p = p->prox;
		}
	
		printf("Digite '0' em 'Codigo:' para finalizar compra.\n");
		printf("Codigo: ");
		scanf("%d", &cod);
		while(cod != 0)
		{
			//verificando existência do produto
			q = busca(cod, *P);
			if(q != NULL)
			{
				printf("Quantidade: ");
				scanf("%d", &qtde);
				printf("\n");

				if(q->qtde == 0)
					printf("Produto em falta.\n\n");
				else if(q->qtde > qtde) //se há produtos em estoque e a quantidade for suficiente para a compra
				{   //inserindo produto no início da lista de compras
					Cnovo = (listaCompra*) malloc(sizeof(listaCompra));
					Cnovo->prox = Vnovo->lst;
					Vnovo->lst = Cnovo;

					Cnovo->cod = q->cod;
					Cnovo->preco = qtde * q->preco;
					Cnovo->qtde = qtde;

					q->qtde -= qtde;
					q->I = 1;
				}
				else if(q->qtde < qtde) //se há produtos em estoque e a quantidade for insuficiente para a compra
				{
					printf("Quantidade em estoque: %d\n", q->qtde);
					printf("Continuar compra ? (S/N): ");
					scanf(" %c", &i);
					if(i == 'S' || i == 's')
					{	//inserindo produto no início da lista de compras
						Cnovo = (listaCompra*) malloc(sizeof(listaCompra));
						Cnovo->prox = Vnovo->lst;
						Vnovo->lst = Cnovo;

						Cnovo->cod = q->cod;
						Cnovo->preco = qtde * q->preco;
						Cnovo->qtde = qtde;

						q->qtde = 0;
						q->I = 1;

						printf("\n");
					}
				}
			}

			printf("Codigo: ");
			scanf("%d", &cod);
		}

		//calculando valor total da compra
		c = Vnovo->lst;
		Vnovo->total = 0;
		while(c != NULL)
		{		
			Vnovo->total += c->preco;
			c = c->prox;
		}
		printf("\nPreco final: R$%.2f\n", Vnovo->total);
	}
}

void inserir_prod(int cod, char *nome, float preco, int qtde, listaProd **P)
{
	listaProd *novo, *p, *q = NULL;

	p = *P;

	//alocação da lista de produtos inicial
	novo = (listaProd*) malloc(sizeof(listaProd));
	novo->cod = cod;
	strcpy(novo->nome, nome);
	novo->preco = preco;
	novo->qtde = qtde;
	novo->ant = NULL;
	novo->prox = NULL;
	novo->I = 0;

	//ordenando lista
	if(p == NULL)
	{
		novo->ant = NULL;
		novo->prox = NULL;
		*P = novo;
	}
	else
	{
		while(p != NULL && p->cod < novo->cod)
		{
			q = p;
			p = p->prox;
		}	
		
		novo->prox = p;
		novo->ant = q;

		if(q == NULL)
			*P = novo;
		else
			q->prox = novo;

		if(p != NULL)
			p->ant = novo;
	}
}

listaProd *busca(int cod, listaProd *P)
{
	listaProd *p;
	p = P;

	while (p != NULL && p->cod != cod) 
		p = p->prox;

	if(p == NULL)
	{
		printf("Codigo nao encontrado\n\n");
		return NULL;
	}
	else
		return p;
}

void alterar(listaProd **lst)
{
	listaProd *p;
	int C, Q;
	float P;

	printf("Codigo: ");
	scanf("%d", &C);

	//busca produto e atualiza seu preço e quantidade
	p = busca(C, *lst);
	if(p != NULL)
	{
		printf("Nome: %s\n"
			   "Preco: R$%.2f\n"
			   "Quantidade: %d\n\n", p->nome, p->preco, p->qtde);
	
		printf("Novo preco: ");
		scanf("%f", &P);
		printf("Quantidade a ser adicionada: ");
		scanf("%d", &Q);

		p->preco = P;
		p->qtde += Q;
	}
}

void remover_dupl(listaProd **P, listaProd *p)
{
	listaProd *q;

	//separando remoção por situação em que o nó se encontra
	if(p->ant == NULL && p->prox != NULL)
	{
		q = p->prox;
		q->ant = NULL;
		*P = q;
	}
	else if(p->ant != NULL && p->prox == NULL)
	{
		q = p->ant;
		q->prox = NULL;
	}
	else if(p->ant != NULL && p->prox != NULL)
	{
		q = p->ant;
		q->prox = p->prox;

		q = p->prox;
		q->ant = p->ant;
	}
	else if(p->ant == NULL && p->prox == NULL)
		*P = NULL;

	free(p);
}

void remover(listaProd **P)
{
	listaProd *p;
	int C;

	printf("Codigo: ");
	scanf("%d", &C);

	//procura o produto e o remove se  I != 1
	p = busca(C, *P);
	if(p != NULL)
	{
		printf("%s\n", p->nome);
		if(p->I == 1)
			printf("Produto nao pode ser removido.\n");
		else
			remover_dupl(P, p);
	}

	if(*P == NULL)
		printf("\nTodos os produtos foram removidos do estoque.\n");
}

void listar(listaVendas **V)
{
	listaVendas *v;
	char data[10];
	int i = 0;

	printf("Data: ");
	scanf("%s", data);
	printf("\n");

	//imprime todas as compras realizadas em tal data
	v = *V;
	while(v != NULL)
	{
		if(strncmp(data, v->data, 10) == 0)
		{
			i = 1;
			printf("Data: %s\n"
				   "Hora: %s\n"
				   "CPF: %s\n"
				   "Valor da compra: R$%.2f\n\n", v->data, v->hora, v->cpf, v->total);
		}

		v = v->prox;
	}

	if(i == 0)
		printf("Nao ha vendas registradas nessa data.\n");
}

void desalocar_v(listaVendas **V)
{
	listaVendas *aux;

    while( *V != NULL)
    {
        aux = *V;

        *V = aux->prox;

        free(aux);
    }
}

void desalocar_p(listaProd **P)
{
	listaProd *aux;

    while( *P != NULL)
    {
        aux = *P;

        *P = aux->prox;

        free(aux);
    }
}

void desalocar_c(listaCompra **C)
{
	listaCompra *aux;

    while( *C != NULL)
    {
        aux = *C;

        *C = aux->prox;

        free(aux);
    }
}