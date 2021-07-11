# lista-encadeada-mercado
Implementação de listas encadeadas na simulação de caixa de mercado.

## Descrição
Este foi um trabalho de Algorítmos e Programação II do curso de Engenharia de Computação (UFMS), em 2019-2, onde deveria ser usada a estrutura de dados de listas encadeadas (simples e duplas) para armazenar os produtos de um mercado, as compras de um cliente e o registro de vendas.</br>
Deveria ser possível o registrar compras, vendas e produtos; Alterar preço e quantidade de um produto e remover produtos do estoque.</br>
O objetivo é o exercício da implementação e manipulação de listas encadeadas, leitura de arquivo de texto, uso de argumentos na linha de comando, alocação dinâmica (ponteiros) e criação de bibliotecas em C.</br></br>

Há pequenas descrições das funções no arquivo .h

## Lista Encadeada

Uma lista encadeada em C é implementada através de structs. É chamada de encadeada por conta de cada nó da lista armazenar o endereço do próximo nó, no caso de uma lista duplamente encadeada, cada nó armazena os endereço dos nós anterior e posterior. </b>
```
typedef struct lista_c
{
	int cod;
	float preco;
	int qtde;
	struct lista_c *prox;
} listaCompra;
```
O bloco acima se trata da declaração da estrutura do nó de lista simples representando uma compra. O endereço do próximo nó é armazenado na variável \*prox do tipo lista_c.</b>
```
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
```
Este já se trata da estrutura do nó de uma lista duplamente encadeada que representa um produto em estoque, já que possui variáveis para armazenar o nó anterior (\*ant) e posterior (\*prox).

## Compilação e Execução

Para compilar os códigos, o comando mais simples a ser usado é o seguinte:
```
gcc -o <nome do executável> main.c funcoes.c
```
E para a execução, é necessário acrescentar o nome do arquivo de texto que contenha as informações dos produtos a serem cadastrados no seguinte formato:
```
CÓDIGO DO PRODUTO
NOME DO PRODUTO
PREÇO
QUANTIDADE
...
CÓDIGO DO PRODUTO
NOME DO PRODUTO
PREÇO
QUANTIDADE
```
Sendo "produtos.txt" o nome desse arquivo, a execução na linha de comando deve ser da seguinte forma (para Windows):
```
main produtos.txt
```
E para Linux:
```
./main produtos.txt
```
Então o arquivo é lido, os produtos são adicionados à uma lista encadeada e o menu do algorítmo é aberto para a interação com as listas.</br>
