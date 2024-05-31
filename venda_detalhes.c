#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "venda_detalhes.h"
#include "venda.h"
#include "menu.h"
#include "evento.h"
#include "components.h"

typedef struct {
    int id_produto;
    char descricao_produto[51];
    int quantidade_total;
    double valor_total;
} Produto_Acumulado;

void salvarVendaDetalhes(Venda_detalhes venda_detalhes) {
    FILE *file;
    char filename[] = "data/vendas_detalhes.txt";
    file = fopen(filename, "a"); // Abrir o arquivo em modo de escrita, acrescentando ao final

    if (file != NULL) {
        fprintf(file, "%d %d %d %d '%s' %d %f\n", venda_detalhes.id, venda_detalhes.id_venda, venda_detalhes.id_produto, venda_detalhes.id_evento,
                venda_detalhes.descricao_produto, venda_detalhes.quantidade_produto, venda_detalhes.valor_produto);
        fclose(file);
        centralizarFrase("--------        Produto da venda salvos com sucesso!        --------", "success");
    } else {
        centralizarFrase("Não foi possível abrir o arquivo.","error");
    }
}

int relatorioVendaEspecificoAux() {
    int escolhaIdVenda;
    int idMax = carregarUltimaVenda();

    do {
        system("cls");
        listarVendas();
        escolhaIdVenda = centralizarEObterValorInt(
                "Escolha o codigo da venda que deseja ver o relatorio (ou digite 0 para SAIR): ");

        switch (escolhaIdVenda) {
            case 0:
                relatorioVendasAux();
                break;
            default:
                if (escolhaIdVenda < 1 || escolhaIdVenda >= idMax) {
                    opcaoInvalida();
                } else {
                    relatorioVendaEspecifico("vendas_detalhes.txt", escolhaIdVenda);
                }
        }
    } while (escolhaIdVenda != 0 && (escolhaIdVenda < 1 || escolhaIdVenda >= idMax));
    //relatorioVendaEspecificoAux();
    return 0;
}

int relatorioEventoEspecificoAux() {
    int escolhaIdRelatorio = 0;
    int idMax = carregarUltimoEvento();

    do {
        system("cls");
        listarEventos();
        escolhaIdRelatorio = centralizarEObterValorInt(
                "Escolha o codigo do evento que deseja ver o relatorio (ou digite 0 para SAIR): ");

        switch (escolhaIdRelatorio) {
            case 0:
                relatorioVendasAux();
                break;
            default:
                if (escolhaIdRelatorio < 1 || escolhaIdRelatorio >= idMax) {
                    opcaoInvalida();
                } else {
                    relatorioEventoEspecifico("vendas_detalhes.txt", escolhaIdRelatorio);
                }
        }
    } while (escolhaIdRelatorio != 0 && (escolhaIdRelatorio < 1 || escolhaIdRelatorio >= idMax));

    return 0;
}

void criteriosOrdenacao() {
    char criterio[15];
    char ordem[15];
    int criterioOpcao;
    int ordemOpcao;

    imprimirTituloCabecarioDuplo("ESCOLHA O CRITERIO DE ORDENACAO",NULL);
    centralizarFrase("1. ID do Produto                   ", "default");
    centralizarFrase("2. Quantidade de Produtos Vendidos ", "default");
    imprimirLinhaDivisoria();
    criterioOpcao = centralizarEObterValorInt("Escolha uma opcao: ");
    imprimirLinhaDivisoria();

    if (criterioOpcao == 1) {
        strcpy(criterio, "id");
    } else if (criterioOpcao == 2) {
        strcpy(criterio, "quantidade");
    } else {
        centralizarFrase("Opcao invalida. Usando 'id' como padrao.","warning");
        strcpy(criterio, "id");
    }

    imprimirTituloCabecarioDuplo("ESCOLHA A ORDEM DE ORDENACAO",NULL);
    centralizarFrase("1. Crescente                       ", "default");
    centralizarFrase("2. Decrescente                     ", "default");
    imprimirLinhaDivisoria();
    ordemOpcao = centralizarEObterValorInt("Escolha uma opcao: ");
    imprimirLinhaDivisoria();
    if (ordemOpcao == 1) {
        strcpy(ordem, "crescente");
    } else if (ordemOpcao == 2) {
        strcpy(ordem, "decrescente");
    } else {
        centralizarFrase("Opcao invalida. Usando 'crescente' como padrao.","warning");
        strcpy(ordem, "crescente");
    }
    system("cls");
    relatorioVendasGeral(criterio, ordem);
}

void relatorioVendasAux(){
    int opcaoEvento = 999;
    while(opcaoEvento != 0) {
    system("cls");
        imprimirTituloCabecarioDuplo("ESCOLHA UMA OPCAO DE RELATORIO", NULL);
        imprimirUsuarioEData();
        printf("| Opcao |   Descricao                                                                                              |\n");
        imprimirLinhaDivisoria();
        printf("|   1   |   Relatorio Geral                                                                                        |\n");
        printf("|   2   |   Relatorio de cada Evento                                                                               |\n");
        printf("|   3   |   Relatorio de cada Venda                                                                                |\n");
        imprimirLinhaDivisoria();
        printf("|   0   |   Menu administrativo                                                                                    |\n");
        imprimirLinhaDivisoria();
        opcaoEvento = centralizarEObterValorInt("Escolha uma opcao: ");
        switch (opcaoEvento) {
            case 1:
                system("cls");
                criteriosOrdenacao();
                break;
            case 2: {
                system("cls");
                relatorioEventoEspecificoAux();
                break;
            }
            case 3: {
                system("cls");
                relatorioVendaEspecificoAux();
                break;
            }
            case 0:
                system("cls");
                centralizarFrase("Saindo da tela de relatorio!", "warning");
                menuAdministrador();
            default:
                opcaoInvalida();
        }
    }
}

int compararProdutosPorIdCrescente(const void* a, const void* b) {
    return ((Produto_Acumulado*)a)->id_produto - ((Produto_Acumulado*)b)->id_produto;
}

int compararPorIdCrescente(const void *a, const void *b) {
    return ((Venda_detalhes*)a)->id_produto - ((Venda_detalhes*)b)->id_produto;
}

int compararPorIdDecrescente(const void *a, const void *b) {
    return ((Venda_detalhes*)b)->id_produto - ((Venda_detalhes*)a)->id_produto;
}

int compararPorQuantidadeCrescente(const void *a, const void *b) {
    return ((Venda_detalhes*)a)->quantidade_produto - ((Venda_detalhes*)b)->quantidade_produto;
}

int compararPorQuantidadeDecrescente(const void *a, const void *b) {
    return ((Venda_detalhes*)b)->quantidade_produto - ((Venda_detalhes*)a)->quantidade_produto;
}

int juntarProdutos(Venda_detalhes* vendas, int count, Produto_Acumulado* produtos) {
    int produtosCount = 0;

    for (int i = 0; i < count; i++) {
        int j;
        for (j = 0; j < produtosCount; j++) {
            if (produtos[j].id_produto == vendas[i].id_produto) {
                produtos[j].quantidade_total += vendas[i].quantidade_produto;
                produtos[j].valor_total += (vendas[i].quantidade_produto * vendas[i].valor_produto);
                break;
            }
        }
        if (j == produtosCount) {
            produtos[produtosCount].id_produto = vendas[i].id_produto;
            strcpy(produtos[produtosCount].descricao_produto, vendas[i].descricao_produto);
            produtos[produtosCount].quantidade_total = vendas[i].quantidade_produto;
            produtos[produtosCount].valor_total = (vendas[i].quantidade_produto * vendas[i].valor_produto);
            produtosCount++;
        }
    }

    return produtosCount;
}

int relatorioVendaEspecifico(const char *nomeArquivo, int opcao) {
    char caminhoArquivo[100];
    strcpy(caminhoArquivo, "data/");
    strcat(caminhoArquivo, nomeArquivo);
    FILE *file = fopen(caminhoArquivo, "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    char *nomeEvento = obterNomeEvento("venda.txt", opcao);
    if (nomeEvento == NULL) {
        nomeEvento = (char*)malloc(strlen("Nada encontrado") + 1);
        if (nomeEvento != NULL) {
            strcpy(nomeEvento, "Nada encontrado");
        } else {
            perror("Erro ao alocar memória para 'Nada encontrado'");
        }
    }

    Venda_detalhes vendas[1000];
    int count = 0;

    // Ler todas as vendas do arquivo
    while (fscanf(file, "%d %d %d %d '%50[^']' %d %lf", &vendas[count].id, &vendas[count].id_venda,
                  &vendas[count].id_produto, &vendas[count].id_evento, vendas[count].descricao_produto,
                  &vendas[count].quantidade_produto, &vendas[count].valor_produto) != EOF) {
        if (vendas[count].id_venda == opcao) {
            count++;
        }
    }
    fclose(file);

    Produto_Acumulado produtos[1000];
    int produtosCount = juntarProdutos(vendas, count, produtos);
    qsort(produtos, produtosCount, sizeof(Produto_Acumulado), compararProdutosPorIdCrescente);
    double accTotal = 0;
    int accQtd = 0;

    // Imprimir cabeçalho da tabela
    system("cls");
    imprimirTituloCabecarioDuplo("RELATORIO ESPECIFICO PARA CADA VENDA", NULL);
    imprimirUsuarioEData();
    printf("| %-15s | %-63s | %-10s | %-6s | %-6s |\n", "Cod", "Produto", "Quantidade", "Valor", "Total");
    imprimirLinhaDivisoria();

    if (produtosCount == 0) {
        imprimirLinhaDivisoria();
        centralizarFrase("Nenhuma venda encontrada para o evento especificado.", "warning");
        imprimirLinhaDivisoria();
    } else {
        for (int i = 0; i < produtosCount; i++) {
            accTotal += produtos[i].valor_total;
            accQtd += produtos[i].quantidade_total;
            printf("| %-15d | %-63s | %-10d | %-6.2lf | %-6.2lf | \n",
                   produtos[i].id_produto, produtos[i].descricao_produto, produtos[i].quantidade_total,
                   produtos[i].valor_total / produtos[i].quantidade_total,
                   produtos[i].valor_total);
        }
        imprimirLinhaDivisoria();
        printf("|                       --------     TOTAL GERAL     --------                      |  QTD   %-3d |  R$      %6.2lf  |\n", accQtd, accTotal);
        imprimirLinhaDivisoria();
    }
    free(nomeEvento);
    int sair;
    while (sair != 0) {
        sair = centralizarEObterValorInt("Digite 0 para sair: ");
    }
    relatorioVendaEspecificoAux();
    return 0;
}


int relatorioEventoEspecifico(const char *nomeArquivo, int opcao) {
    char caminhoArquivo[100];
    strcpy(caminhoArquivo, "data/");
    strcat(caminhoArquivo, nomeArquivo);
    FILE *file = fopen(caminhoArquivo, "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    char *nomeEvento = obterNomeEvento("eventos.txt", opcao);
    if (nomeEvento == NULL) {
        nomeEvento = (char*)malloc(strlen("Nada encontrado") + 1);
        if (nomeEvento != NULL) {
            strcpy(nomeEvento, "Nada encontrado");
        } else {
            perror("Erro ao alocar memória para 'Nada encontrado'");
        }
    }

    Venda_detalhes vendas[1000];
    int count = 0;

    // Ler todas as vendas do arquivo
    while (fscanf(file, "%d %d %d %d '%50[^']' %d %lf", &vendas[count].id, &vendas[count].id_venda,
                  &vendas[count].id_produto, &vendas[count].id_evento, vendas[count].descricao_produto,
                  &vendas[count].quantidade_produto, &vendas[count].valor_produto) != EOF) {
        if (vendas[count].id_evento == opcao) {
            count++;
        }
    }
    fclose(file);

    Produto_Acumulado produtos[1000];
    int produtosCount = juntarProdutos(vendas, count, produtos);
    qsort(produtos, produtosCount, sizeof(Produto_Acumulado), compararProdutosPorIdCrescente);
    double accTotal = 0;
    int accQtd = 0;

    // Imprimir cabeçalho da tabela
    system("cls");
    imprimirTituloCabecarioDuplo("RELATORIO ESPECIFICO PARA CADA EVENTO", nomeEvento);
    imprimirUsuarioEData();
    printf("| %-15s | %-63s | %-10s | %-6s | %-6s |\n", "Cod", "Produto", "Quantidade", "Valor", "Total");
    imprimirLinhaDivisoria();

    if (produtosCount == 0) {
        imprimirLinhaDivisoria();
        centralizarFrase(" Nenhuma venda encontrada para o evento especificado.", "warning");
        imprimirLinhaDivisoria();
    } else {
        for (int i = 0; i < produtosCount; i++) {
            accTotal += produtos[i].valor_total;
            accQtd += produtos[i].quantidade_total;
            printf("| %-15d | %-63s | %-10d | %-6.2lf | %-6.2lf | \n",
                   produtos[i].id_produto, produtos[i].descricao_produto, produtos[i].quantidade_total,
                   produtos[i].valor_total / produtos[i].quantidade_total,
                   produtos[i].valor_total);
        }
        imprimirLinhaDivisoria();
        printf("|                       --------     TOTAL GERAL     --------                       |  QTD   %-3d |  R$     %6.2lf  |\n", accQtd, accTotal);
        imprimirLinhaDivisoria();
    }
    int sair;
    while (sair != 0) {
        sair = centralizarEObterValorInt("Digite 0 para sair: ");
    }
    relatorioEventoEspecificoAux();
    return 0;
}



int relatorioVendasGeral(char* criterio, char* ordem) {
    FILE *file;
    char filename[] = "data/vendas_detalhes.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        // Imprimir cabeçalho da tabela
        imprimirTituloCabecarioDuplo("RELATORIO GERAL DAS VENDAS", NULL);
        imprimirUsuarioEData();
        printf("| %-15s | %-63s | %-10s | %-6s | %-6s |\n", "Cod", "Produto", "Quantidade", "Valor", "Total");
        imprimirLinhaDivisoria();

        fseek(file, 0, SEEK_END);
        if (ftell(file) == 0) {
            imprimirLinhaDivisoria();
            centralizarFrase(" Nenhuma venda encontrada.", "warning");
            imprimirLinhaDivisoria();
            fclose(file);
            return 0;
        }
        rewind(file);

        Venda_detalhes vendas[1000];
        int count = 0;

        while (fscanf(file, "%d %d %d %d '%50[^']' %d %lf", &vendas[count].id, &vendas[count].id_venda,
                      &vendas[count].id_produto, &vendas[count].id_evento, vendas[count].descricao_produto,
                      &vendas[count].quantidade_produto, &vendas[count].valor_produto) != EOF) {
            count++;
        }
        fclose(file);

        if (strcmp(criterio, "id") == 0) {
            if (strcmp(ordem, "crescente") == 0) {
                qsort(vendas, count, sizeof(Venda_detalhes), compararPorIdCrescente);
            } else {
                qsort(vendas, count, sizeof(Venda_detalhes), compararPorIdDecrescente);
            }
        } else if (strcmp(criterio, "quantidade") == 0) {
            if (strcmp(ordem, "crescente") == 0) {
                qsort(vendas, count, sizeof(Venda_detalhes), compararPorQuantidadeCrescente);
            } else {
                qsort(vendas, count, sizeof(Venda_detalhes), compararPorQuantidadeDecrescente);
            }
        }

        Produto_Acumulado produtos[1000];
        int produtosCount = juntarProdutos(vendas, count, produtos);

        double accTotal = 0;
        int accQtd = 0;

        for (int i = 0; i < produtosCount; i++) {
            accTotal += produtos[i].valor_total;
            accQtd += produtos[i].quantidade_total;
            printf("| %-15d | %-63s | %-10d | %-6.2lf | %-6.2lf | \n",
                   produtos[i].id_produto, produtos[i].descricao_produto, produtos[i].quantidade_total,
                   produtos[i].valor_total / produtos[i].quantidade_total,
                   produtos[i].valor_total);
        }

        imprimirLinhaDivisoria();
        printf("|                       --------     TOTAL GERAL     --------                       |  QTD   %-3d |  R$     %6.2lf  |\n", accQtd, accTotal);
        imprimirLinhaDivisoria();
        // Opção para alterar a ordenação
        //imprimirTituloCabecario("Digite 1 para alterar a ordenacao ou 0 para sair", NULL);
        int opcaoOrdenacao;
        opcaoOrdenacao = centralizarEObterValorInt("Digite 1 para alterar a ordenacao ou 0 para sair: ");
        //Sleep(1000);
        if (opcaoOrdenacao == 1) {
            system("cls");
            criteriosOrdenacao();
        }
    } else {
        centralizarFrase("Não foi possível abrir o arquivo.","error");
    }
    centralizarFrase("Retornando ao menu anterior","warning");
    system("cls");
    return 0;
}


int carregarUltimaVendaDetalhes() {
    FILE *file;
    char filename[] = "data/vendas_detalhes.txt";
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
        centralizarFrase("Não foi possível abrir o arquivo.","error");
    }

    return contador_linhas+1;
}

