#include<stdio.h>
#include<stdlib.h>

void limparTela();
void exibirMenu();

int main()
{
    exibirMenu();	

    return 0;
}

void exibirMenu()
{
    int escolha = 0;
    
    limparTela();

    printf("---MENU PRINCIPAL--- \n");
    printf(" 1.Cadastros \n 2.Vendas \n 3.Abertura de Caixa \n 4.Fechamento de caixa \n 5.Relatórios \n 6.Sair \n");
    
    while(escolha == 0)
    {
        scanf("%d", &escolha);
	if(escolha < 1 || escolha > 6) 
	{
	    printf("Escolha uma opção entre 1 e 6!");
	    escolha = 0;
	};
    };
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
