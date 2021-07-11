/***************************************************
* Tiago Clarintino Santi
* Trabalho
* Professor(a): Graziela Santos de Araujo
*/

#include "funcoes.h"

int main(int argc, char *argv[])
{
	FILE *entrada;
	listaVendas *V = NULL, *v;
	listaProd *P = NULL;

	int x = 0;
	
	char *arquivo;
	
	int cod;
	char nome[30];
	float preco;
	int qtde;

	if(argc != 2)
	{
		printf("Erro na linha de comando\n");
		return 0;
	}

	arquivo = argv[1];

	entrada = fopen(arquivo, "r");
	if(!entrada)
		printf("Nao foi possivel abrir o arquivo %s\n", arquivo);
	else
	{	//scan das informações dos produtos
		fscanf(entrada, "%d", &cod);
		fscanf(entrada, " %[^\n]", nome);
		fscanf(entrada, "%f", &preco);
		fscanf(entrada, "%d", &qtde);
		inserir_prod(cod, nome, preco, qtde, &P);
		while(!feof(entrada))
		{	//scan das informações dos produtos
			fscanf(entrada, "%d", &cod);
			fscanf(entrada, " %[^\n]", nome);
			fscanf(entrada, "%f", &preco);
			fscanf(entrada, "%d", &qtde);	
			inserir_prod(cod, nome, preco, qtde, &P);	
		}
 
		do
		{
			//menu principal do programa
			printf("Menu:\n"
				   "[1] Cadastrar Venda\n"
				   "[2] Listar vendas por data\n"
				   "[3] Alterar estoque e preco de produto\n"
				   "[4] Remover produto do estoque\n"
				   "[5] Sair\n"
				   "Opcao: ");
			scanf("%d", &x);
			printf("\n");

			if(x == 1)
			{
				cadastrar(&V, &P);
				printf("\n");
			}
			if(x == 2)
			{
				listar(&V);
				printf("\n");
			}

			if(x == 3)
			{
				alterar(&P);
				printf("\n");
			}

			if(x == 4)
			{
				remover(&P);
				printf("\n");
			}

		} while(x != 5);

		desalocar_v(&V);
		desalocar_p(&P);

		v = V;
		while(v != NULL)
			desalocar_c(&v->lst);

		fclose(entrada);
	}

	return 0;
}
