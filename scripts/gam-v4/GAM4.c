#include<stdio.h> // Biblioteca para poder usar printf(), scanf() e outros...
#include<stdlib.h> // Biblioteca para usarmos outras funções prontas...
#include<locale.h> // Para usar setlocale() e escolher o idioma do programa.
#include<stdbool.h> // Biblioteca para usarmos dado booleano, true ou false.

typedef struct
{
    char nome[50];
    int codigo;
    int estoque;
    float precoCompra;
    float precoVenda;
} Produto;

void limparTela();   // Estas duas funções verificam se o sistema operacional é
void limparBuffer(); // Windows ou linux, e usam as funções próprias para ele.
void menuPrincipal();
void menuCadastros();
void menuAbrirCaixa();
void abrirCaixa();
void cadastrarProduto();
bool codigoUnico(); // Verifica se o código do produto já está sendo usado.
void menuRelatorios();
void relatorioDosProdutos();
void exibirProdutos();

int main()
{
    setlocale(LC_ALL, "");
    menuPrincipal();
    //funcao();

    return 0;
}

void limparTela()
{
    #ifdef _WIN32
	system("cls");
    #elif __linux__
	system("clear");
    #endif
}

void limparBuffer()
{
    #ifdef _WIN32
	fflush(stdin);
    #elif __linux__
	__fpurge(stdin);
    #endif
}

void menuPrincipal()
{
    int escolha = 0;

    limparTela();

    printf("***Mercearia da Berênice***\n");
    printf("~Menu Principal~\n\n");
    printf("1.Cadastros\n3.Abrir caixa\n5.Relatórios\n6.Sair\n\n");
    printf("Escolha uma opção: ");
    
    while(true)
    {
        scanf("%d", &escolha);
	switch(escolha)
	{
	    case 1: menuCadastros();     break;
	    case 3: menuAbrirCaixa();    break;
	    case 5: menuRelatorios();    break;
 	    case 6: exit(0);             break;

	    default: printf("\nOpção inválida! escolha outra opção: ");
	}
    }

}

void menuCadastros()
{
    int escolha = 0;

    limparTela();

    printf("***Mercearia da Berênice***\n");
    printf("~Menu de cadastros~\n\n");
    printf("1.Cadastrar produto\n6.Voltar\n\n");
    printf("Escolha uma opção: ");
    
    while(true)
    {
        scanf("%d", &escolha);
	switch(escolha)
	{
	    case 1: cadastrarProduto();    break;
 	    case 6: menuPrincipal();       break;

	    default: printf("\nOpção inválida! escolha outra opção: ");
	}
    }

}

void cadastrarProduto()
{
    limparTela();

    int tamanho = 0;
    Produto produto;
    Produto *produtos;
    FILE *arquivoProdutos = fopen("produtos.bin", "rb");
    
    if(arquivoProdutos == NULL)
    {
	arquivoProdutos = fopen("produtos.bin", "wb+");
    }
    
    fread(&tamanho, sizeof(tamanho), 1, arquivoProdutos);
    produtos = (Produto *) calloc(tamanho+1, sizeof(Produto));
    fread(produtos, sizeof(Produto), tamanho, arquivoProdutos);
    fclose(arquivoProdutos);

    printf("***Mercearia da Berênice***\n");
    printf("~Cadastrar novo produto~\n\n");
    printf("Código do produto: ");
    scanf("%d", &produto.codigo);
    printf("Nome do produto: ");
    limparBuffer();
    scanf("%50[^\n]", produto.nome);
    printf("Preço de compra: ");
    scanf("%f", &produto.precoCompra);
    printf("Preço de venda: ");
    scanf("%f", &produto.precoVenda);
    printf("Quantidade em estoque: ");
    scanf("%d", &produto.estoque);

    if(codigoUnico(produto.codigo, tamanho, produtos) == false)
    {
        printf("\n\nEste código de produto já está sendo usado!\n");
        printf("Pressione Enter para voltar . . .");
        free(produtos);
	limparBuffer();
        getchar();
        menuCadastros();
    }

    produtos[tamanho] = produto;
    tamanho++;

    arquivoProdutos = fopen("produtos.bin", "wb");
    fwrite(&tamanho, sizeof(tamanho), 1, arquivoProdutos);
    fwrite(produtos, sizeof(Produto), tamanho, arquivoProdutos);
    fclose(arquivoProdutos);

    free(produtos);

    printf("\nProduto cadastrado!\nPressione Enter para voltar . . .");
    limparBuffer();
    getchar();
    menuCadastros();
}

bool codigoUnico(int codigo, int tamanho, Produto *produtos)
{
    for(int i = 0; i < tamanho; i++)
    {
        if(codigo == produtos[i].codigo)
	    return false;
    }   
    return true;
}

void vender()
{
    exibirProdutos();

    printf("Escolha um produto: ");
}

void menuAbrirCaixa()
{
    int escolha = 0;
    
    limparTela();

    printf("***Mercearia da Berênice***\n");
    printf("~Abrir caixa~\n\n");
    printf("1.Abrir caixa\n2.Voltar ao menu principal\n\n");
    printf("Escolha uma opção: ");
    
    while(true)
    {
        scanf("%d", &escolha);
	switch(escolha)
	{
	    case 1: abrirCaixa();       break;
 	    case 2: menuPrincipal();    break;

	    default: printf("\nOpção inválida! escolha outra opção: ");
	}
    }
}

void abrirCaixa()
{
    float caixa = -1;
    FILE *arquivoCaixa = fopen("arquivoCaixa.bin", "wb");

    if(arquivoCaixa == NULL)
    {
        printf("\nErro ao abrir arquivo de caixa.\n");
	printf("Pressione Enter para continuar . . .");
	limparBuffer();
	getchar();
	menuPrincipal();
    }

    printf("\nValor em caixa: ");
    while(caixa < 0)
    {    
	scanf("%f", &caixa);
	if(caixa < 0)
	{
	    printf("Valor inválido! informe novamente: ");
	}
    }

    fwrite(&caixa, sizeof(caixa), 1, arquivoCaixa);
    fclose(arquivoCaixa);

    printf("Caixa aberto com sucesso! Pressione Enter para voltar . . .");
    limparBuffer();
    getchar();
    menuPrincipal();
}

void menuRelatorios()
{
    int escolha = 0;

    limparTela();

    printf("***Mercearia da Berênice***\n");
    printf("~Menu de relatórios~\n\n");
    printf("1.Listar produtos\n6.Voltar\n\n");
    printf("Escolha uma opção: ");
    
    while(true)
    {
        scanf("%d", &escolha);
	switch(escolha)
	{
	    case 1: relatorioDosProdutos();    break;
 	    case 6: menuPrincipal();          break;

	    default: printf("\nOpção inválida! escolha outra opção: ");
	}
    }
}

void relatorioDosProdutos()
{
    exibirProdutos();
    printf("Pressione Enter para voltar . . .");
    limparBuffer();
    getchar();
    menuRelatorios();
}

void exibirProdutos()
{
    limparTela();
    
    int tamanho = 0;
    Produto *produtos;
    FILE *arquivoProdutos = fopen("produtos.bin", "rb");

    if(arquivoProdutos == NULL)
    {
	arquivoProdutos = fopen("produtos.bin", "wb+");
    }

    fread(&tamanho, sizeof(tamanho), 1, arquivoProdutos);
    produtos = (Produto *) calloc(tamanho, sizeof(Produto));
    fread(produtos, sizeof(Produto), tamanho, arquivoProdutos);
    fclose(arquivoProdutos);

    printf("***Mercearia da Berênice***\n");
    printf("~Lista de produtos~\n\n");
    printf("%d produto(s)\n\n", tamanho);
    for(int i = 0; i < tamanho; i++)
    {
        printf("Produto %d\n", produtos[i].codigo);
	printf("Nome: %s\n", produtos[i].nome);
        printf("Preço de compra: %.2f\n", produtos[i].precoCompra);
        printf("Preço de venda: %.2f\n", produtos[i].precoVenda);
	printf("Quantidade em estoque: %d\n\n", produtos[i].estoque);
	printf("**********************************************\n\n");
    }

    free(produtos);    
}
