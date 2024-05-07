#include <stdio.h>
#include <string.h>
#include "produto.h"

void criarProduto() {
    Produto produto;
    char p_descricao[51]; // Array de caracteres para armazenar a descrição
    int p_preco = 0;
    int p_estoque = 0;

    // Solicitar ao usuário que insira os dados do produto
    printf("========================================================\n");
    printf("|            TELA DE CADASTRO DE PRODUTOS              |\n");
    printf("|------------------------------------------------------|\n");
    printf("|\tDigite a descricao do produto: ");
    scanf(" %50[^\n]", p_descricao); // Lê a descrição até uma nova linha ou 99 caracteres
    printf("|\tDigite o preco do produto: ");
    scanf("%d", &p_preco);
    printf("|\tDigite o estoque do produto: ");
    scanf("%d", &p_estoque);
    printf("|------------------------------------------------------|\n");

    // Preencher a estrutura do produto com os dados inseridos
    produto.id = carregarUltimoProduto() ; // Incrementar o ID do último produto
    strcpy(produto.descricao, p_descricao);
    produto.preco = p_preco;
    produto.estoque = p_estoque;
    produto.id_evento = 1; // Preciso receber como parâmetro - TODO

    // Salvar o produto
    salvarProduto(produto);

    printf("Produto criado com sucesso.\n");
}

int listarProdutos() {
    FILE *file;
    char filename[] = "data/produtos.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        //printf("Arquivo foi aberto com sucesso.\n\n");

        // Imprimir cabeçalho da tabela

        printf("|=========================================================================|\n");
        printf("|                            LISTA DE PRODUTOS                            |\n");
        printf("|-------------------------------------------------------------------------|\n");
        printf("| %-3s | %-35s | %-5s | %-7s | %-9s |\n", "Cod", "Descricao", "Preco", "Estoque", "Evento");
        printf("|-----|-------------------------------------|-------|---------|-----------|\n");

        Produto produto;

        // Ler e exibir cada linha do arquivo
        while (fscanf(file, "%d '%[^']' %lf %d %d", &produto.id, produto.descricao, &produto.preco, &produto.estoque, &produto.id_evento ) != EOF) {
            printf("| %-3d | %-35s | %-5.2f | %-7d | %-9d |\n", produto.id, produto.descricao, produto.preco, produto.estoque, produto.id_evento);
        }

        printf("|-------------------------------------------------------------------------|\n");
        fclose(file);
    } else {
        printf("Não foi possível abrir o arquivo %s.\n\n", filename);
    }

    return 0;
}

int carregarUltimoProduto() {
    FILE *file;
    char filename[] = "data/produtos.txt";
    file = fopen(filename, "r");

    int contador_linhas = 0;

    if (file != NULL) {
        int c;
        // Percorrer o arquivo caractere por caractere
        while ((c = fgetc(file)) != EOF) {
            if (c == '\n') {
                ++contador_linhas;
            }
        }
        fclose(file);
        //printf("|\tRegistro %d\n", contador_linhas);
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }

    return contador_linhas+1;
}

void salvarProduto(Produto produto) {
    FILE *file;
    char filename[] = "data/produtos.txt";
    file = fopen(filename, "a"); // Abrir o arquivo em modo de adição para adicionar no final

    if (file != NULL) {
        // Escrever os dados do produto no arquivo
        fprintf(file, "%d '%s' %.2f %d %d\n", produto.id, produto.descricao, produto.preco, produto.estoque, produto.id_evento);
        fclose(file);
        printf("Produto salvo com sucesso.\n");
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }
}


Produto consultarProdutoPorID(int id) {
    FILE *file;
    char filename[] = "data/produtos.txt";
    file = fopen(filename, "r"); // Abrir o arquivo em modo de leitura

    if (file != NULL) {
        Produto produto;
        int encontrado = 0;

        // Lê cada produto do arquivo até encontrar o produto com o ID correspondente
        while (fscanf(file, "%d '%50[^']' %lf %d %d\n", &produto.id, produto.descricao, &produto.preco,
                      &produto.estoque, &produto.id_evento) != EOF) {
            if (produto.id == id) {
                encontrado = 1;
                fclose(file);
                return produto;
            }
        }

        fclose(file);
        if (!encontrado) {
            printf("Produto com ID %d não encontrado.\n", id);
        }
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }

    Produto produto_vazio; // Retorna um produto vazio se não encontrar
    produto_vazio.id = -1; // Ou outro valor que você considerar adequado
    return produto_vazio;
}


