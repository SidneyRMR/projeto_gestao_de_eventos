#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "produto.h"
#include "components.h"
#include "evento.h"
#include "menu.h"
#include "variaveis_compartilhadas.h"

void criarProduto() {
    Produto produto;

    imprimirTituloCabecario("TELA DE CADASTRO DE PRODUTOS",NULL);

    // Solicitar ao usuário que insira os dados do produto
    char *p_descricao = centralizarEObterValorChar("Digite a descricao do produto: ", 51);
    strncpy(produto.descricao, p_descricao, sizeof(produto.descricao) - 1);

    double p_preco = centralizarEObterValorDouble("Digite o preco do produto: ");

    int p_estoque = centralizarEObterValorInt("Digite o estoque do produto: ");

    imprimirLinhaDivisoria();

    // Preencher a estrutura do produto com os dados inseridos
    produto.id = carregarUltimoProduto() ; // Incrementar o ID do último produto
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
        imprimirUsuarioEData();
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

void atualizarProduto(Produto produto) {
    FILE *file;
    char filename[] = "data/produtos.txt";
    FILE *tempFile;
    char tempFilename[] = "data/temp.txt";
    Produto tempProduto;

    file = fopen(filename, "r");
    tempFile = fopen(tempFilename, "w");

    if (file != NULL && tempFile != NULL) {
        while (fscanf(file, "%d '%99[^']' %lf %d %d\n", &tempProduto.id, tempProduto.descricao, &tempProduto.preco, &tempProduto.estoque, &tempProduto.id_evento) != EOF) {
            if (tempProduto.id == produto.id) {
                fprintf(tempFile, "%d '%s' %.2lf %d %d\n", produto.id, produto.descricao, produto.preco, produto.estoque, produto.id_evento);
            } else {
                fprintf(tempFile, "%d '%s' %.2lf %d %d\n", tempProduto.id, tempProduto.descricao, tempProduto.preco, tempProduto.estoque, tempProduto.id_evento);
            }
        }
        fclose(file);
        fclose(tempFile);

        // Remover o arquivo original e renomear o arquivo temporário
        remove(filename);
        rename(tempFilename, filename);

        printf("Produto atualizado com sucesso.\n");
    } else {
        if (file == NULL) {
            printf("Erro ao abrir o arquivo %s.\n", filename);
        }
        if (tempFile == NULL) {
            printf("Erro ao criar o arquivo temporário %s.\n", tempFilename);
        }
    }
}

Produto carregarProdutoPorID(int id) {
    FILE *file;
    char filename[] = "data/produtos.txt";
    Produto produto;

    file = fopen(filename, "r");
    if (file != NULL) {
        while (fscanf(file, "%d '%99[^']' %lf %d %d\n", &produto.id, produto.descricao, &produto.preco, &produto.estoque, &produto.id_evento) != EOF) {
            if (produto.id == id) {
                fclose(file);
                return produto;
            }
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }

    // Retornar um produto vazio caso não seja encontrado
    Produto produtoNaoEncontrado = {0, "", 0.0, 0, 0};
    return produtoNaoEncontrado;
}

void adicionarEstoque(int id, int quantidade) {
    Produto produto = carregarProdutoPorID(id);
    produto.estoque += quantidade;
    atualizarProduto(produto);
    printf("Estoque atualizado com sucesso.\n");
}

void removerEstoque(int id, int quantidade) {
    id = id * -1;
    Produto produto = carregarProdutoPorID(id);
    if (produto.estoque >= quantidade) {
        produto.estoque -= quantidade;
        atualizarProduto(produto);
        printf("Estoque atualizado com sucesso.\n");
    } else {
        printf("Quantidade insuficiente em estoque.\n");
    }
}

int ajustarEstoque() {
    int opcaoProdutoEstoque;
    int idMax = carregarUltimoProduto();
    int quantidade;

    imprimirLinhaDivisoria();
    listarProdutos();
    centralizarFrase("Digite o codigo de um produto para adicionar ao estoque (0 - Sair)");
    centralizarFrase("Digite o '-'e codigo do produto para remover do estoque (0 - Sair)");
    imprimirLinhaDivisoria();
    opcaoProdutoEstoque = centralizarEObterValorInt("Escolha uma opcao: ");

    if (opcaoProdutoEstoque > 0 && opcaoProdutoEstoque <= idMax-1) {
        quantidade = centralizarEObterValorInt("Digite quantos produtos deseja ADICIONAR:");
        adicionarEstoque(opcaoProdutoEstoque, quantidade);
        system("cls");
        ajustarEstoque();
    } else if(opcaoProdutoEstoque < 0 && opcaoProdutoEstoque >= -idMax+1) {
        quantidade = centralizarEObterValorInt("Digite quantos produtos deseja REMOVER:");
        removerEstoque(opcaoProdutoEstoque, quantidade);
        system("cls");
        ajustarEstoque();
    } else if ((opcaoProdutoEstoque > 0 && opcaoProdutoEstoque > idMax-1) || (opcaoProdutoEstoque < 0 && opcaoProdutoEstoque < -idMax+1)){
        system("cls");
        opcaoInvalida();
        ajustarEstoque();
    }
    return 0;
}
