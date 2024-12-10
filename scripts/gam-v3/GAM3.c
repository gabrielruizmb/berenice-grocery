#include<stdio.h>     // Biblioteca para usarmos scanf/printf...
#include<stdlib.h>    // Biblioteca para usarmos a função de limpar a tela.
#include<string.h>    // Biblioteca para usarmos string.

void limparTela();           // função que limpa a tela;
void menu();		     // função que exibe o menu principal.
void menuCadastros();        // função que exibe o menu de cadastros.
void cadastrarClientes();    // função para cadastrar novo cliente.
void limparBuffer();	     // função que limpa o buffer para depois usarmos fgets, getchar...

typedef struct
{
    int codigo;
    char nome[50];
    char nomeSocial[50];
    char cpfOuCnpj[19];
    char bairro[50];
    char rua[50];
    char numero[10];
    char telefone[15]; 
} cliente;

cliente clientes[20];
int clientesCadastrados = 0;

int main()
{
    menu();	

    return 0;
}

void menu()
{
    int escolha = 0;

    limparTela();
    
    printf("---MENU PRINCIPAL--- \n");
    printf(" 1.Cadastros \n 2.Vendas \n 3.Abertura de Caixa \n 4.Fechamento de caixa \n 5.Relatórios \n 6.Sair \n");
    
    while(escolha == 0)
    {
        scanf("%d", &escolha);

	switch(escolha)
	{
	    case 1: menuCadastros(); break;
            case 6: exit(0);

   	    default: 
		printf("Opção inválida! escolha entre 1 e 6.");
		escolha = 0;
	}
    };
}

void menuCadastros()
{
    int escolha = 0;

    limparTela();
    printf("1.Cadastro \n");
    printf(" 11.Cadastro de clientes \n 12.Cadastro de produtos \n 13.Voltar ao menu principal \n");
    
    while(escolha == 0)
    {
        scanf("%d", &escolha);
        switch(escolha)
        {
	    case 11: cadastrarClientes();    break;
            case 13: menu();		     break;

	    default: 
		 printf("Opção inválida! escolha entre 11 e 13.");
		 escolha = 0;
        }
    }
}

void cadastrarClientes()
{
    limparTela();
    
    printf("Informe o código do cliente: ");
    scanf("%d", &clientes[clientesCadastrados].codigo);

    printf("Informe o nome do cliente: ");
    limparBuffer();
    fgets(clientes[clientesCadastrados].nome, 50, stdin);

    printf("Informe o nome social do cliente(deixe em branco para nenhum): ");
    limparBuffer();
    fgets(clientes[clientesCadastrados].nomeSocial, 50, stdin);

    printf("Informe o cpf/cpnj: ");
    limparBuffer();
    fgets(clientes[clientesCadastrados].cpfOuCnpj, 19, stdin);

    printf("Informe o bairro: ");
    limparBuffer();
    fgets(clientes[clientesCadastrados].bairro, 50, stdin);

    printf("Informe a rua: ");
    limparBuffer();
    fgets(clientes[clientesCadastrados].rua, 50, stdin);

    printf("Informe o número: ");
    limparBuffer();
    fgets(clientes[clientesCadastrados].numero, 10, stdin);

    printf("Informe o telefone: ");
    limparBuffer();
    scanf("%50[^\n]", clientes[clientesCadastrados].telefone);
  
    printf("Cliente cadastrado com sucesso! Pressione qualquer tecla para continuar. \n");
    clientesCadastrados++;

    limparBuffer();
    getchar();
    menu();
}

void limparTela()
{
    // Se o sistema operacional usado for Linux, execute isto:
    #ifdef __linux__
	system("clear");

    // Se for Windows, execute isto:
    #elif _WIN32
	system("cls");
    #else

    #endif
}

void limparBuffer()
{
    // A mesma lógica da função limparTela(), mas desta vez com a função de limpar o Buffer.
    #ifdef __linux__
	__fpurge(stdin);
    #elif _WIN32
	fflush(stdin);
    #else

    #endif
}
