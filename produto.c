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

    imprimirTituloCabecarioDuplo("TELA DE CADASTRO DE PRODUTOS", NULL);

    // Solicitar ao usuário que insira os dados do produto
    char *p_descricao = centralizarEObterValorChar("Digite a descricao do produto: ", 51);
    double p_preco = centralizarEObterValorDouble("Digite o preco do produto: ");
    int p_estoque = centralizarEObterValorInt("Digite o estoque do produto: ");

    listarEventosCadastro();
    int eventoMax = carregarUltimoEvento();
    int opcaoEvento = 0;

    do {
        opcaoEvento = centralizarEObterValorInt("Digite o codigo do evento para o usuario: ");
    } while(opcaoEvento < 1 || opcaoEvento >= eventoMax);


// Convertendo valores para strings
    char str_preco[20];
    char str_estoque[20];
    sprintf(str_preco, "%.2f", p_preco);
    sprintf(str_estoque, "%d", p_estoque);
    char* nomeEvento = obterNomeEvento("eventos.txt", opcaoEvento);

// Imprimir os valores lidos
    imprimirTituloCabecarioLista("Valores lidos", NULL);
    centralizarFraseDoisValores("Descricao: ", p_descricao);
    centralizarFraseDoisValores("Preco:     ", str_preco);
    centralizarFraseDoisValores("Estoque:   ", str_estoque);
    centralizarFraseDoisValores("Evento:    ", nomeEvento);
    imprimirLinhaLista();

    // Preencher a estrutura do produto com os dados inseridos
    produto.id = carregarUltimoProduto(); // Incrementar o ID do último produto
    strncpy(produto.descricao, p_descricao, sizeof(produto.descricao) - 1);
    produto.preco = p_preco;
    produto.estoque = p_estoque;
    produto.id_evento = opcaoEvento;
    // Solicitar confirmação
    char confirmacao[4];
    do {
        strcpy(confirmacao, centralizarEObterValorChar("Confirme se os valores estao corretos (sim/nao): ", 3));
        getchar(); // Limpar o buffer do teclado

        if (strcmp(confirmacao, "nao") == 0) {
            system("cls");
            criarProduto(); // Chamada recursiva para inserir os valores novamente
            return; // Retorna após a chamada recursiva para evitar continuar o loop
        }

    } while (strcmp(confirmacao, "sim") != 0);
    // Salvar o produto
    salvarProduto(produto);

    centralizarFrase("Produto criado com sucesso.");
}

int listarProdutos() {
    FILE *file;
    char filename[] = "data/produtos.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        imprimirTituloCabecario("LISTA DE PRODUTOS", NULL);
        imprimirUsuarioEData();

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


void editarProduto(int idProduto, int idEvento){
    //todo
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



Produto BuscarProdutoPorID(int id) {
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

        centralizarFrase("Produto atualizado com sucesso.");
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
    centralizarFrase("Estoque atualizado com sucesso.");
}

void removerEstoque(int id, int quantidade) {
    id = id * -1;
    Produto produto = carregarProdutoPorID(id);
    if (produto.estoque >= quantidade) {
        produto.estoque -= quantidade;
        atualizarProduto(produto);
        centralizarFrase("Estoque atualizado com sucesso.");
    } else {
        centralizarFrase("Quantidade insuficiente em estoque.");
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
int EditarNomeProduto(int idProduto){}
int EditarDescricaoProduto(int idProduto){}
int DesativarProduto(int idProduto){}