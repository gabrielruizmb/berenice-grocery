#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

void clearScreen();
void mainMenu();

int main()
{
    setlocale(LC_ALL, "");
    mainMenu();

    return 0;
}

void mainMenu()
{
    clearScreen();
    printf("***Mercearia da Berenice***\n\nMenu principal:\n\n");
    printf("  1.Cadastros\n  2.Vendas\n  3.Abertura de caixa\n");
    printf("  4.Fechamento de caixa\n  5,Relatórios\n  6.Sair\n\n");
}

void clearScreen()
{
    #ifdef __linux__
        system("clear");

    #elif _WIN32
	system("cls");

    #endif
}
