#include<stdio.h>
#include<stdlib.h>

void limparTela();
void menu();
void menuCadastros();
void cadastrarClientes();

typedef struct
{
    int codigo;
    char nome[50];
    char nomeSocial[50];
    char cpfOuCnpj[19];
    char bairro[50];
    char rua[50];
    char numero[10];
    char numeroDeTelefone[15]; 
} cliente;

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
	    case 12: cadastrarClientes();    break;
            case 13: menu();		     break;

	    default: 
		 printf("Opção inválida! escolha entre 11 e 13.");
		 escolha = 0;
        }
    }
}

void cadastrarClientes()
{
    
}

void limparTela()
{
    #ifdef __linux__
	system("clear");
    #elif _WIN32
	system("cls");
    #else

    #endif
}
