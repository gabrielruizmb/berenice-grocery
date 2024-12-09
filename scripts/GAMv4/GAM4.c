#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<stdbool.h>

typedef struct
{
    int codigo;
    float preco;
} Produto;

void limparTela();
void limparBuffer();
void menuPrincipal();
void menuCadastros();
void cadastrarProduto();
void menuRelatorios();
void relatorioDosProdutos();
void funcao();

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
    printf("1.Cadastros\n5.Relatórios\n6.Sair\n\n");
    printf("Escolha uma opção: ");
    
    while(true)
    {
        scanf("%d", &escolha);
	switch(escolha)
	{
	    case 1: menuCadastros();     break;
	    case 5: relatorioDosProdutos();    break;
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
    FILE *arquivoProdutos = fopen("arquivos\\produtos.bin", "rb");
    Produto *produtos;
    Produto produto;

    fread(&tamanho, sizeof(tamanho), 1, arquivoProdutos);
    produtos = (Produto *) calloc(tamanho, sizeof(Produto));
    fread(produtos, sizeof(Produto), tamanho, arquivoProdutos);
    fclose(arquivoProdutos);

    printf("***Mercearia da Berênice***\n");
    printf("~Cadastrar novo produto~\n\n");
    printf("Código do produto: ");
    scanf("%d", &produto.codigo);
    printf("Preço do produto: ");
    scanf("%f", &produto.preco);
    
    produtos[tamanho] = produto;
    tamanho++;

    arquivoProdutos = fopen("arquivos\\produtos.bin", "wb");
    fwrite(&tamanho, sizeof(tamanho), 1, arquivoProdutos);
    fwrite(produtos, sizeof(Produto), tamanho, arquivoProdutos);
    fclose(arquivoProdutos);

    free(arquivoProdutos);
    free(produtos);

    printf("\nProduto cadastrado!\nPressione Enter para voltar . . .");
    limparBuffer();
    getchar();
    menuCadastros();
}

void relatorioDosProdutos()
{
    limparTela();

    FILE *arquivoProdutos = fopen("arquivos\\produtos.bin", "rb");
    int tamanho = 0;
    Produto *produtos;

    fread(&tamanho, sizeof(tamanho), 1, arquivoProdutos);
    produtos = (Produto *) calloc(tamanho, sizeof(Produto));
    fread(produtos, sizeof(Produto), tamanho, arquivoProdutos);
    fclose(arquivoProdutos);
    free(arquivoProdutos);

    printf("***Mercearia da Berênice***\n");
    printf("~Lista de produtos~\n\n");
    printf("%d produtos\n\n", tamanho);
    for(int i = 0; i < tamanho; i++)
    {
        printf("Produto %d\n", produtos[i].codigo);
        printf("Preço: %.2f\n\n", produtos[i].preco);
    }
    free(produtos);
    
    printf("Pressione Enter para voltar . . .");
    limparBuffer();
    getchar();
    menuPrincipal();
}

void funcao()
{
    int tamanho = 0;
    Produto produto;
    produto.codigo = 101;
    produto.preco = 1.50;

    FILE *arquivoProdutos;
    Produto *produtos = (Produto *) calloc(tamanho, sizeof(produto));
    
    produtos[tamanho] = produto;
    tamanho++;

    arquivoProdutos = fopen("arquivos\\produtos.bin", "wb"); 
    fwrite(&tamanho, sizeof(tamanho), 1, arquivoProdutos);
    fwrite(produtos, sizeof(produto), 1, arquivoProdutos);
    fclose(arquivoProdutos);
    free(arquivoProdutos);
    
    tamanho = 100;
    produto.codigo = 0;
    produto.preco = 0;
    
    arquivoProdutos = fopen("arquivos\\produtos.bin", "rb");
    fread(&tamanho, sizeof(tamanho), 1, arquivoProdutos);
    fread(produtos, sizeof(produto), 1, arquivoProdutos);
    fclose(arquivoProdutos);
    free(arquivoProdutos);

    printf("Tamanho da lista de produtos: %d\n\n", tamanho);
    for(int i = 0; i < tamanho; i++)
    {
        printf("Código: %d\n", produtos[i].codigo);
	printf("Preço: %.2f\n", produtos[i].preco);
    }
    free(produtos);
}
