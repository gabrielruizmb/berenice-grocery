#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
void menuPrincipal();
int buscarPosicaoPorChave();
int contarRegistros();
void exibirListaDeProdutos();
bool inserirProdutoNaLista();
void inserirProduto();
void limparTela();
void limparBuffer();
void menuCadastros();
void menuRelatorios();

int main()
{
    setlocale(LC_ALL, "");
    
    Lista lista;
    inicializarLista(&lista);
    menuPrincipal(&lista);
   
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

void limparBuffer()
{
    // A mesma lógica da função limparTela(), mas desta vez com a função de limpar o Buffer.
    #ifdef __linux__
	__fpurge(stdin);

    #elif _WIN32
	fflush(stdin);

    #endif
}

void menuPrincipal(Lista *lista)
{
    limparTela();

    int escolha = 0;

    printf("*** Mercearia da Berênice ***\n");
    printf("~Menu principal~\n\n");
    printf("1.Inserir produto\n5.Relatórios\n6.Sair\n\n");
    printf("Escolha uma opção: ");
    
    while(true)
    {
        scanf("%d", &escolha);
	switch(escolha)
	{
	    case 1: menuCadastros(lista);     break;
            case 5: menuRelatorios(lista);    break;
	    case 6: exit(0);		      break;
	    default: printf("Opção inválida! escolha outra opção: ");
	}
    }
}

void menuCadastros(Lista *lista)
{
    limparTela();

    int escolha = 0;

    printf("*** Mercearia da Berênice ***\n");
    printf("~Menu de cadastros~\n\n");
    printf("3.Cadastrar produto\n4.Voltar ao menu principal\n\n");
    printf("Escolha uma opção: ");
    
    while(true)
    {
        scanf("%d", &escolha);
	switch(escolha)
	{
	    case 3: inserirProduto(lista);    break;
	    case 4: menuPrincipal(lista);     break;
	    default: printf("Opção inválida! escolha outra opção: ");
	}
    }
}

void inserirProduto(Lista *lista)
{
    int posicao = 0, escolha = 0;
    Produto produto;
    
    limparTela();
    printf("*** Mercearia da Berênice ***\n");
    printf("~Cadastrar novo produto~\n\n");
    
    printf("Informe a chave do produto: ");
    scanf("%d", &produto.chave);

    printf("Informe o preço do produto: ");
    scanf("%f", &produto.preco);

    if(inserirProdutoNaLista(lista, produto, posicao) == false)
	printf("\nEsta chave já está sendo usada! Escolha outra chave.\n\n");
    else 
	printf("\nProduto inserido!\n\n");
	
    printf("Pressione a tecla Enter para voltar ao menu de cadastros. . .");
    limparBuffer();
    getchar();
    menuCadastros(lista);
}

void menuRelatorios(Lista *lista)
{
    int escolha = 0;

    limparTela();
    printf("***Mercearia da Berênice***\n");
    printf("~Menu de relatórios~\n\n");
    printf("2.Listar produtos\n4.Voltar ao menu principal\n\n");
    printf("Escolha uma opção: ");
    while(true)
    {
        scanf("%d", &escolha);
	switch(escolha)
	{
	    case 2: exibirListaDeProdutos(lista);    break;
	    case 4: menuPrincipal(lista);    	     break;
	    default: printf("Opção inválida! Escolha uma opção: ");
	}
    }
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

void exibirListaDeProdutos(Lista *lista)
{
    for(int i = 0; i < lista->quantidade; i++)
    {
        printf("Código: %d\nPreço: %f\n", lista->produtos[i].chave, lista->produtos[i].preco);
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
        lista->produtos[j] = lista->produtos[j-1];
    }
    lista->produtos[posicao] = produto;
    lista->quantidade++;
    
    //0 1 2 3 4    0 1 2 3 4 5
    //A B C D E    X A B C D E

    return true;    
}


