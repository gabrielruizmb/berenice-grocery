#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<locale.h>
#define tamanho 10

typedef int tipoChave;

typedef struct
{
    tipoChave chave;
    float preco;
} Produto;

typedef struct
{
    Produto produtos[tamanho];
    int quantidade;
} Lista;

void inicializarLista();
int buscarPosicaoPorChave();
int contarRegistros();
void exibirLista();
bool inserirProdutoNaLista();
void inserirProduto();
void limparTela();

int main()
{
    setlocale(LC_ALL, "");
    limparTela();

    Lista lista;
    inicializarLista(&lista);

    int escolha = 0;

    printf("*** Mercearia da Berênice ***\n");
    printf("~Menu principal~\n\n");
    printf("1.Inserir produto\n2.Sair\n\n");
    printf("Escolha uma opção: ");
    
    while(true)
    {
        scanf("%d", &escolha);
	switch(escolha)
	{
	    case 1: inserirProduto(&lista);    break;
 	    case 2: exit(0);		       break;

	    default: printf("Opção inválida! escolha outra opção: ");
	}
    }
    
    return 0;
}

void limparTela()
{
    #ifdef __linux__
	system("clear");

    #elif _WIN32
	system("cls");

    #endif
}

void inicializarLista(Lista *lista)
{
    lista->quantidade = 0;
}

int buscarPosicaoPorChave(Lista *lista, tipoChave chave)
{
    int i = 0;

    while(i < lista->quantidade)
    {
        if(chave == lista->produtos[i].chave)
	{
	    return i;
	}
	i++;
    }

    return -1;
}

int contarRegistros(Lista *lista)
{
    return lista->quantidade;
}

void exibirLista(Lista *lista)
{
    for(int i = 0; i < lista->quantidade; i++)
    {
        printf("%d %f", lista->produtos[i].chave, lista->produtos[i].preco);
    }
}

bool inserirProdutoNaLista(Lista *lista, Produto produto, int posicao)
{
    if(posicao < 0 || posicao > lista->quantidade || lista->quantidade == tamanho)
    {
        //printf("\nPosição inválida!");
	return false;
    }
     
    if(buscarPosicaoPorChave(lista, produto.chave) != -1)
    {
	//printf("\nEsta chave já está sendo usada!");
	return false;
    }

    for(int j = lista->quantidade; j > posicao; j--)
    {
        lista->produtos[j] = lista->produtos[j--];
    }
    lista->produtos[posicao] = produto;
    lista->quantidade++;

    return true;    
}

void inserirProduto(Lista *lista)
{
    limparTela();

    int posicao = 0;
    
    Produto produto;
    printf("Informe a chave do produto: ");
    scanf("%d", &produto.chave);

    printf("Informe o preço do produto: ");
    scanf("%f", &produto.preco);

    if(inserirProdutoNaLista(lista, produto, posicao) == false)
	printf("Esta chave já está sendo usada!");
    else 
	printf("\nProduto inserido!");
}
