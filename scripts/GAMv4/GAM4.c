#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int codigo;
    float preco;
} Produto;

int main()
{
    int tamanho = 1;
    Produto produto;
    produto.codigo = 101;
    produto.preco = 1.50;

    FILE *arquivoProdutos;

    arquivoProdutos = fopen("arquivos\\produtos.bin", "wb"); 
    fwrite(&tamanho, sizeof(tamanho), 1, arquivoProdutos);
    fwrite(&produto, sizeof(produto), 1, arquivoProdutos);
    fclose(arquivoProdutos);
    free(arquivoProdutos);
    
    tamanho = 100;
    produto.codigo = 0;
    produto.preco = 0;

    arquivoProdutos = fopen("arquivos\\produtos.bin", "rb");
    fread(&tamanho, sizeof(tamanho), 1, arquivoProdutos);
    fread(&produto, sizeof(produto), 1, arquivoProdutos);
    fclose(arquivoProdutos);
    free(arquivoProdutos);

    printf("Tamanho da lista de produtos: %d", tamanho);
    printf("\n\nCódigo: %d\nPreço: %.2f\n", produto.codigo, produto.preco);

    return 0;
}
