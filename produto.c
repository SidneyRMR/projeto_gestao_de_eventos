#include <stdio.h>
#include <string.h>
#include "produto.h"
#include "components.h"
#include "evento.h"
#include "menu.h"
#include "variaveis_compartilhadas.h"

void criarProduto() {
    Produto produto;
    char p_descricao[51]; // Array de caracteres para armazenar a descrição
    int p_preco = 0;
    int p_estoque = 0;

    imprimirTituloCabecario("TELA DE CADASTRO DE PRODUTOS",NULL);

    // Solicitar ao usuário que insira os dados do produto
    printf("|\tDigite a descricao do produto: ");
    scanf(" %50[^\n]", p_descricao); // Lê a descrição até uma nova linha ou 99 caracteres
    printf("|\tDigite o preco do produto: ");
    scanf("%d", &p_preco);
    printf("|\tDigite o estoque do produto: ");
    scanf("%d", &p_estoque);
    imprimirLinhaDivisoria();

    // Preencher a estrutura do produto com os dados inseridos
    produto.id = carregarUltimoProduto() ; // Incrementar o ID do último produto
    strcpy(produto.descricao, p_descricao);
    produto.preco = p_preco;
    produto.estoque = p_estoque;

    listarEventosCadastro();
    int eventoMax = carregarUltimoEvento();
    int opcaoEvento = 0;

    do {
        printf("|\tDigite o codigo do evento para o usuario: ");
        scanf("%d", &opcaoEvento);
    }
    while(opcaoEvento < 1 || opcaoEvento > eventoMax);

    produto.id_evento = opcaoEvento;

    // Salvar o produto
    salvarProduto(produto);

    printf("\tProduto criado com sucesso.\n");
}

int listarProdutos() {
    FILE *file;
    char filename[] = "data/produtos.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        //printf("Arquivo foi aberto com sucesso.\n\n");
        imprimirRodape();
        // Imprimir cabeçalho da tabela
        imprimirTituloCabecario("LISTA DE PRODUTOS", NULL);

        printf("| %-3s | %-63s | %-10s | %-9s | %-15s |\n", "Cod", "Descricao", "Preco", "Estoque", "Evento");
        imprimirLinhaDivisoria();

        Produto produto;

        // Ler e exibir cada linha do arquivo
        while (fscanf(file, "%d '%[^']' %lf %d %d", &produto.id, produto.descricao, &produto.preco, &produto.estoque, &produto.id_evento ) != EOF) {
            char evento[10];
            char* nomeEvento = obterNomeEvento("eventos.txt", produto.id_evento);

            printf("| %-3d | %-63s | %-10.2f | %-9d | %-15s |\n", produto.id, produto.descricao, produto.preco, produto.estoque, nomeEvento);
        }

        imprimirLinhaDivisoria();
        fclose(file);
    } else {
        printf("Não foi possível abrir o arquivo %s.\n\n", filename);
    }

    return 0;
}
int listarProdutosVenda() {
    FILE *file;
    char filename[] = "data/produtos.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        //printf("Arquivo foi aberto com sucesso.\n\n");
        imprimirRodape();
        // Imprimir cabeçalho da tabela
        imprimirTituloCabecario("LISTA DE PRODUTOS", NULL);

        printf("| %-3s | %-75s | %-10s | %-15s |\n", "Cod", "Descricao", "Preco", "Estoque");
        imprimirLinhaDivisoria();

        Produto produto;

        // Ler e exibir cada linha do arquivo
        while (fscanf(file, "%d '%[^']' %lf %d %d", &produto.id, produto.descricao, &produto.preco, &produto.estoque, &produto.id_evento ) != EOF) {
            if(produto.id_evento != getUsuarioCompartilhado().id_evento) continue;

            printf("| %-3d | %-75s | %-10.2f | %-15d |\n", produto.id, produto.descricao, produto.preco, produto.estoque);
        }

        imprimirLinhaDivisoria();
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


