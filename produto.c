#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "produto.h"
#include "components.h"
#include "evento.h"
#include "menu.h"
#include "variaveis_compartilhadas.h"

void erroAoAbrirArquivo() {
    centralizarFrase("Não foi possível abrir o arquivo.","error");
}

void criarProduto() {
    Produto produto;

    imprimirTituloCabecarioDuplo("TELA DE CADASTRO DE PRODUTOS", NULL);
    centralizarFrase("Digite 0 a qualquer momento para sair","warning");
    imprimirLinhaDivisoria();

    // Solicitar ao usuário que insira os dados do produto
    char *p_descricao = centralizarEObterValorChar("Digite a descricao do produto: ", 50);
    if (strcmp(p_descricao, "0") == 0) {
        return; // Sai da função se o usuário digitar 0
    }
    double p_preco;
    do {
        p_preco = centralizarEObterValorDouble("Digite o preco do produto: ");
        if (p_preco == 0.0) {
            return; // Sai da função se o usuário digitar 0
        }
        if (p_preco > 1000) {
            printf("Erro: O preço não pode ser maior que 1000. Por favor, insira novamente.\n");
        }
    } while (p_preco > 1000);

    int p_estoque;
    do {
        p_estoque = centralizarEObterValorInt("Digite o estoque do produto: ");
        if (p_estoque == 0) {
            return; // Sai da função se o usuário digitar 0
        }
        if (p_estoque > 1000) {
            printf("Erro: O estoque não pode ser maior que 1000. Por favor, insira novamente.\n");
        }
    } while (p_estoque > 1000);

    listarEventosCadastro();
    int eventoMax = carregarUltimoEvento();
    int opcaoProduto = 0;
    do {
        opcaoProduto = centralizarEObterValorInt("Digite o codigo do evento para o usuario: ");
        if (opcaoProduto == 0) {
            return; // Sai da função se o usuário digitar 0
        }
    } while(opcaoProduto < 1 || opcaoProduto >= eventoMax);


// Convertendo valores para strings
    char str_preco[20];
    char str_estoque[20];
    sprintf(str_preco, "%.2f", p_preco);
    sprintf(str_estoque, "%d", p_estoque);
    char* nomeEvento = obterNomeEvento("eventos.txt", opcaoProduto);

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
    produto.id_evento = opcaoProduto;
    produto.status = 1;

    // Solicitar confirmação
    char confirmacao[4];
    do {
        strcpy(confirmacao, centralizarEObterValorChar("Confirme se os valores estao corretos (sim/nao): ", 3));
        if (strcmp(confirmacao, "0") == 0) {
            return; // Sai da função se o usuário digitar 0
        }

        if (strcmp(confirmacao, "nao") == 0) {
            system("cls");
            criarProduto(); // Chamada recursiva para inserir os valores novamente
            return; // Retorna após a chamada recursiva para evitar continuar o loop
        }

    } while (strcmp(confirmacao, "sim") != 0);
    // Salvar o produto
    salvarProduto(produto);

    //centralizarFrase("Produto criado com sucesso.", "success");
}

int listarProdutos() {
    FILE *file;
    char filename[] = "data/produtos.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        imprimirTituloCabecario("LISTA DE PRODUTOS", NULL);
        imprimirUsuarioEData();

        printf("| %-3s | %-50s | %-10s | %-9s | %-15s | %-10s |\n", "Cod", "Descricao", "Preco", "Estoque", "Evento", "Status");
        imprimirLinhaDivisoria();

        Produto produto;
        int encontrouProdutos = 0;

        while (fscanf(file, "%d '%[^']' %lf %d %d %d", &produto.id, produto.descricao, &produto.preco, &produto.estoque, &produto.id_evento, &produto.status) != EOF) {
            char* nomeEvento = obterNomeEvento("eventos.txt", produto.id_evento);
            char prodAtivado[11];

            if (produto.status == 1) {
                strcpy(prodAtivado, "Ativo");
            } else {
                strcpy(prodAtivado, "Inativo");
            }
            //rewind(file);
            printf("| %-3d | %-50.50s | %-10.2f | %-9d | %-15.15s | %-10s |\n",
                   produto.id, produto.descricao, produto.preco, produto.estoque, nomeEvento, prodAtivado);
            free(nomeEvento);  // Liberar memória alocada para o nome do evento
            encontrouProdutos = 1;
        }
        if (!encontrouProdutos) {
            centralizarFrase("Nenhum produto encontrado.", "warning");
        }
        imprimirLinhaDivisoria();
        fclose(file);
    } else {
        erroAoAbrirArquivo();
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
    } else {
        erroAoAbrirArquivo();
    }

    return contador_linhas+1;
}

void salvarProduto(Produto produto) {
    FILE *file;
    char filename[] = "data/produtos.txt";
    file = fopen(filename, "a"); // Abrir o arquivo em modo de adição para adicionar no final

    if (file != NULL) {
        // Escrever os dados do produto no arquivo
        fprintf(file, "%d '%s' %.2f %d %d %d\n", produto.id, produto.descricao, produto.preco, produto.estoque, produto.id_evento, produto.status);
        fclose(file);
        centralizarFrase("Produto salvo com sucesso.","success");
    } else {
        erroAoAbrirArquivo();
    }
}



Produto buscarProdutoPorID(int id) {
    FILE *file;
    char filename[] = "data/produtos.txt";
    file = fopen(filename, "r"); // Abrir o arquivo em modo de leitura

    if (file != NULL) {
        Produto produto;
        int encontrado = 0;

        // Lê cada produto do arquivo até encontrar o produto com o ID correspondente
        while (fscanf(file, "%d '%50[^']' %lf %d %d %d\n", &produto.id, produto.descricao, &produto.preco,
                      &produto.estoque, &produto.id_evento, &produto.status) != EOF) {
            if (produto.id == id) {
                encontrado = 1;
                fclose(file);
                return produto;
            }
        }

        fclose(file);
        if (!encontrado) {
            centralizarFrase("Produto com não encontrado.", "warning");
        }
    } else {
        erroAoAbrirArquivo();
    }
    Produto produto_vazio; // Retorna um produto vazio se não encontrar
    produto_vazio.id = -1;
    return produto_vazio;
}

void atualizarProduto(Produto produto) {
    FILE *file;
    char filename[] = "data/produtos.txt";
    FILE *tempFile;
    char tempFilename[] = "data/tempProduto.txt";
    Produto tempProduto;

    file = fopen(filename, "r");
    tempFile = fopen(tempFilename, "w");

    if (file != NULL && tempFile != NULL) {
        while (fscanf(file, "%d '%49[^']' %lf %d %d %d\n", &tempProduto.id, tempProduto.descricao, &tempProduto.preco, &tempProduto.estoque, &tempProduto.id_evento, &tempProduto.status) != EOF) {
            if (tempProduto.id == produto.id) {
                fprintf(tempFile, "%d '%s' %.2lf %d %d %d\n", produto.id, produto.descricao, produto.preco, produto.estoque, produto.id_evento, produto.status);
            } else {
                fprintf(tempFile, "%d '%s' %.2lf %d %d %d\n", tempProduto.id, tempProduto.descricao, tempProduto.preco, tempProduto.estoque, tempProduto.id_evento, tempProduto.status);
            }
        }
        fclose(file);
        fclose(tempFile);

        // Remover o arquivo original e renomear o arquivo temporário
        remove(filename);
        rename(tempFilename, filename);

        centralizarFrase("Produto atualizado com sucesso.", "success");
    } else {
        if (file == NULL) {
            erroAoAbrirArquivo();
        }
        if (tempFile == NULL) {
            centralizarFrase("Não foi possível abrir o arquivo temporario.","error");
        }
    }
}

Produto carregarProdutoPorID(int id) {
    FILE *file;
    char filename[] = "data/produtos.txt";
    Produto produto;

    file = fopen(filename, "r");
    if (file != NULL) {
        while (fscanf(file, "%d '%50[^']' %lf %d %d %d\n", &produto.id, produto.descricao, &produto.preco, &produto.estoque, &produto.id_evento, &produto.status) != EOF) {
            if (produto.id == id) {
                fclose(file);
                return produto;
            }
        }
        fclose(file);
    } else {
        erroAoAbrirArquivo();
    }
    // Retornar um produto vazio caso não seja encontrado
    Produto produtoNaoEncontrado = {0, "", 0.0, 0, 0};
    return produtoNaoEncontrado;
}

void adicionarEstoque(int id, int quantidade) {
    Produto produto = carregarProdutoPorID(id);
    produto.estoque += quantidade;
    atualizarProduto(produto);
    centralizarFrase("Estoque atualizado com sucesso.", "success");
}

void removerEstoque(int id, int quantidade) {
    Produto produto = carregarProdutoPorID(id);
    if (produto.estoque >= quantidade) {
        produto.estoque -= quantidade;
        atualizarProduto(produto);
        centralizarFrase("Estoque atualizado com sucesso.", "success");
    } else {
        centralizarFrase("Quantidade insuficiente em estoque.","warning");
    }
}

int ajustarEstoqueSelecionado(int idProd) {
    int opcaoProdutoEstoque;
    int quantidade;

    opcaoProdutoEstoque = centralizarEObterValorInt("Digite 1 para adicionar ou 2 para remover  (0 - Sair)");
    if (opcaoProdutoEstoque == 1) {
        do {
            quantidade = centralizarEObterValorInt("Digite quantos produtos deseja ADICIONAR:");
            if (quantidade > 1000) {
                centralizarFrase("O estoque nao pode ser maior que 1000. Por favor, insira novamente.","warning");
            }
        } while (quantidade > 1000);
        adicionarEstoque(idProd, quantidade);
        system("cls");
        //menuEditarProduto();
    } else if(opcaoProdutoEstoque == 2) {
        do {
            quantidade = centralizarEObterValorInt("Digite quantos produtos deseja REMOVER:");
            if (quantidade > 1000) {
                centralizarFrase("O estoque nao pode ser maior que 1000. Por favor, insira novamente.","warning");
            }
        } while (quantidade > 1000);
        removerEstoque(idProd, quantidade);
        system("cls");
        //menuEditarProduto();
    } else if(opcaoProdutoEstoque == 0) {
        system("cls");
        menuEditarProduto();
    } else {
        system("cls");
        opcaoInvalida();
        menuEditarProduto();
    }
    system("cls");
    return 0;
}
